# DayZ Enforce Script Guidelines

## Fundamental Rules

1. **NO COMPOUND STATEMENTS** - Split complex conditions into separate if statements
2. **NO MULTIPLE DECLARATION OF CLASSNAMES**
3. **DECLARE ALL VARIABLES AT TOP OF FUNCTION SCOPE**
4. **EARLY RETURNS** - Exit functions early when validation fails
5. **NULL CHECKS FIRST** - Always check objects before accessing them

## Variable Declaration Pattern

```c
void SomeFunction()
{
    // Declare all variables at top
    string modName;
    bool found;
    int count;
    
    // Use variables throughout function
    modName = GetModName();
    found = false;
    
    foreach (int i = 0; i < items.Count(); i++)
    {
        // Reuse variables, don't declare new ones
        modName = items[i].GetName();
        found = CheckItem(modName);
    }
}
```

## Syntax Guidelines

### If Statements
```c
// Single-line if statements don't need braces:
if (!GetGame().IsServer()) return true;

// Multiple statements require braces:
if (!object)
{
    Print("Object is null");
    return;
}

// NEVER use compound conditions, split them:
// WRONG:
// if (!game || !game.GetPVEConfig() || !player) return;

// CORRECT:
if (!game) return;
if (!game.GetPVEConfig()) return;
if (!player) return;
```

### Class Extension
```c
// Use modded keyword to extend vanilla classes
modded class CarScript
{
    override void OnContact(string zoneName, vector localPos, IEntity other, Contact data)
    {
        super.OnContact(zoneName, localPos, other, data);
        // Your code here
    }
}
```

## Memory Management

1. **Use autoptr** for automatic memory cleanup
2. **Inherit from Managed** for safer reference management  
3. **Use ref keyword** for strong references
4. **Clean up timers** and event handlers in OnDelete

```c
// Strong reference with ref keyword
protected ref Timer m_UpdateTimer;

// Clean up in OnDelete
override void OnDelete()
{
    if (m_UpdateTimer && m_UpdateTimer.IsRunning())
    {
        m_UpdateTimer.Stop();
    }
    
    GetDayZGame().Event_OnRespawn.Remove(OnRespawn);
    super.OnDelete();
}
```

## Performance Optimization

1. **Minimize object creation in loops**
2. **Use early returns** instead of deep nesting
3. **Make debug prints conditional**
4. **Cache frequently accessed values**
5. **Avoid unnecessary type casts**
6. **Use appropriate update intervals**

```c
// Cache value instead of recalculating
protected float m_CachedDistance;

// Update at appropriate intervals
protected void StartUpdateTimer()
{
    if (m_UpdateTimer && m_UpdateTimer.IsRunning()) return;
    
    m_UpdateTimer = new Timer();
    m_UpdateTimer.Run(1.0, this, "OnUpdate", null, true);
}
```

## Server-Client Architecture

### Server-Side Validation
```c
if (!GetGame().IsServer()) return;
```

### Client-Side Validation
```c
if (!GetGame().IsClient()) return;
```

### RPC Communication
```c
// Server side
GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msgParam, true, player.GetIdentity());

// Client side
override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) 
{
    if (!GetGame().IsClient()) return;
    super.OnRPC(sender, rpc_type, ctx);
    
    // Handle RPC
}
```

## Design Patterns

### Config Validation Pattern
```c
DayZGame game = DayZGame.Cast(GetGame());
if (!game) return;
if (!game.GetPVEConfig()) return;
if (game.GetPVEConfig().Enabled == 0) return;
```

### Entity Type Handling
```c
// Handle different entity types separately
if (!other) return;

if (other.IsInherited(Building)) return true;
if (other.IsInherited(ZombieBase)) return false;
if (other.IsInherited(AnimalBase)) return false;
```

### Component Access
```c
EntityAI attachment = GetInventory().FindAttachment(component);
if (!attachment) return;

// Check component types individually
if (attachment.IsInherited(CarWheel)) return true;
if (attachment.IsInherited(SparkPlug)) return true;
```

### Event System
```c
// Registration
override void OnInit()
{
    super.OnInit();
    GetDayZGame().Event_OnRespawn.Insert(OnRespawn);
}

// Cleanup
override void OnDelete()
{
    GetDayZGame().Event_OnRespawn.Remove(OnRespawn);
    super.OnDelete();
}
```

### Timer Management
```c
protected ref Timer m_UpdateTimer;

void StartTimer()
{
    if (m_UpdateTimer && m_UpdateTimer.IsRunning()) return;
    
    m_UpdateTimer = new Timer();
    m_UpdateTimer.Run(1.0, this, "OnUpdate", null, true);
}
```

## File Structure

```c
modded class ClassName
{
    // 1. Constants
    const float SOME_VALUE = 1.0;
    
    // 2. Protected members
    protected ref Timer m_Timer;
    
    // 3. Constructor
    void ClassName()
    {
        // Init code
    }
    
    // 4. Override methods
    override void OnInit()
    {
        super.OnInit();
    }
    
    // 5. Custom methods
    protected void CustomMethod()
    {
    }
}
```

## Vehicle Modding

### Vehicle Component Protection
```c
if (component && GetInventory())
{
    EntityAI attachment = GetInventory().FindAttachment(component);
    if (attachment)
    {
        if (attachment.IsInherited(CarWheel)) return true;
        if (attachment.IsInherited(SparkPlug)) return true;
        if (attachment.IsInherited(CarBattery)) return true;
    }
}
```

### Vehicle Collision Handling
```c
override void OnContact(string zoneName, vector localPos, IEntity other, Contact data)
{
    if (!other) return;
    
    // Allow building collisions
    if (other.IsInherited(Building)) return true;
    
    // Prevent specific entity damage
    if (other.IsInherited(ZombieBase)) return false;
    if (other.IsInherited(AnimalBase)) return false;
    if (other.IsInherited(PlayerBase)) return false;
}
```

### Vehicle Speed Checks
```c
float GetSpeedMS()
{
    vector velocity = GetVelocity(this);
    return vector.Length(velocity);
}

bool IsHighSpeed()
{
    return GetSpeedMS() > HIGH_SPEED_THRESHOLD;
}
```

### Damage Prevention
```c
if (game.GetPVEConfig().Settings.GetPreventVehicleDamage())
{
    if (game.GetPVEConfig().Settings.GetDebugMode())
        Print("[PVE Debug] Prevented vehicle damage");
    return false;
}
```

## Config File Handling

### JSON Config Loading
```c
protected bool LoadConfig()
{
    if (FileExist(CONFIG_PATH))
    {
        JsonFileLoader<PVEConfig>.JsonLoadFile(CONFIG_PATH, this);
        return true;
    }
    return false;
}
```

### Example Config Formats
```json
// Damage Settings
{
    "PreventVehicleDamage": 1,
    "PreventVehicleZombieHits": 1,
    "PreventVehicleAnimalHits": 1,
    "AllowBuildingCollisions": 1,
    "DebugMode": 0
}

// Component Protection
{
    "ProtectedComponents": [
        "CarWheel",
        "SparkPlug",
        "CarBattery",
        "CarRadiator"
    ]
}
```

## Debugging

### Debug Configuration
```c
const bool DEBUG_MODE = true;

void DebugMessage(string message)
{
    if (!DEBUG_MODE) return;
    Print("[MyMod] " + message);
}
```

### Performance Monitoring
```c
float start_time = GetGame().GetTime();
// ... operation ...
float end_time = GetGame().GetTime();
Print(string.Format("[Performance] Operation took %1 ms", end_time - start_time));
```

### Vehicle Debug Helper
```c
void DebugVehicle(CarScript vehicle)
{
    if (!GetGame().GetPVEConfig().Settings.GetDebugMode()) return;
    
    Print(string.Format("[Vehicle Debug] %1 - Health: %2, Speed: %3", 
        vehicle.GetType(),
        vehicle.GetHealth(),
        vehicle.GetSpeedMS()));
}
```

## Common DayZ Types

### Essential Types
- PlayerBase
- DayZGame
- EntityAI
- ItemBase
- Building
- CarScript

### Common Collections
- ref array<EntityAI>
- ref array<PlayerBase>
- ref array<string>
- ref map<string, float>

## Common Mistakes to Avoid

1. **Using compound conditions**
2. **Skipping null checks**
3. **Nesting conditions deeply**
4. **Mixing client/server code without checks**
5. **Multiple declarations of the same variable**
6. **Not cleaning up timers and event handlers** 