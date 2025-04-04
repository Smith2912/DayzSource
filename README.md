# DayZ Mod Development Repository

This repository contains modding resources and code based on DayZ's vanilla source files. Use this as a reference for creating custom DayZ mods following proper Enforce Script practices.

## Purpose

- Provide a structured workspace for DayZ mod development
- Maintain reference to vanilla source code
- Implement mod functionality using proper Enforce Script patterns

## Repository Structure

- `/scripts` - Contains mod script files organized in the standard DayZ folder structure
  - `/1_core` - Core functionality and base classes
  - `/2_gamelib` - Game library scripts
  - `/3_game` - Game mechanics
  - `/4_world` - World entities, vehicles, items
  - `/5_mission` - Mission scripts, UI, and player interactions

## Development Guidelines

### Enforce Script Best Practices

- Declare all variables at the top of function scope
- No compound statements
- No multiple declarations of classnames
- Split complex conditions into separate if statements
- Use early returns for validation

### Code Structure Example

```c
modded class MyVehicleClass extends CarScript
{
    // Constants
    const float DAMAGE_MULTIPLIER = 0.5;
    
    // Protected members
    protected ref Timer m_UpdateTimer;
    protected float m_HealthLevel;
    
    override void EEInit()
    {
        super.EEInit();
        
        // Server-side validation 
        if (!GetGame().IsServer()) return;
        
        // Initialize variables
        m_HealthLevel = 1.0;
        
        // Start update cycle
        StartUpdateTimer();
    }
    
    protected void StartUpdateTimer()
    {
        if (m_UpdateTimer && m_UpdateTimer.IsRunning()) return;
        
        m_UpdateTimer = new Timer();
        m_UpdateTimer.Run(1.0, this, "OnUpdate", null, true);
    }
    
    void OnUpdate()
    {
        // Server-side validation
        if (!GetGame().IsServer()) return;
        
        // Debug logging if enabled
        if (GetGame().GetPVEConfig().Settings.GetDebugMode())
            Print("[Vehicle Debug] Updating vehicle state");
            
        // Main update logic
        UpdateVehicleState();
    }
    
    protected void UpdateVehicleState()
    {
        // Implementation code
    }
}
```

### Vehicle Modification Patterns

When working with vehicles, follow these patterns:

1. **Server-Side Validation**
   ```c
   if (!GetGame().IsServer()) return;
   ```

2. **Config Validation**
   ```c
   DayZGame game = DayZGame.Cast(GetGame());
   if (!game) return;
   if (!game.GetPVEConfig()) return;
   if (game.GetPVEConfig().Enabled == 0) return;
   ```

3. **Vehicle Component Protection**
   ```c
   if (component && GetInventory())
   {
       EntityAI attachment = GetInventory().FindAttachment(component);
       if (!attachment) return;
       
       if (attachment.IsInherited(CarWheel)) return true;
       if (attachment.IsInherited(SparkPlug)) return true;
       if (attachment.IsInherited(CarBattery)) return true;
   }
   ```

## Setting Up Your Mod

1. Fork or clone this repository
2. Set up your development environment for DayZ modding
3. Create modded classes that extend vanilla functionality
4. Test in DayZ Workbench
5. Package for workshop using DayZ Tools

## Contributing

If you've created improvements or additions that might benefit others, please submit a pull request following these guidelines:

- Maintain code style and naming conventions
- Document changes thoroughly
- Test all functionality before submission
- Provide screenshots or video of new features in action

## License

This project is for educational purposes. All DayZ game content belongs to Bohemia Interactive.
Your mods created using this project are your own intellectual property. 