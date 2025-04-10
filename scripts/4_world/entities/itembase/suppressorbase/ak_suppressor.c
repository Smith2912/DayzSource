class AK_Suppressor extends ItemSuppressor
{
	override bool CanPutAsAttachment( EntityAI parent )
	{		
		if (!super.CanPutAsAttachment(parent)) 
			return false;
		
		if (parent.IsSlotReserved(InventorySlots.GetSlotIdFromString("suppressorImpro")) || parent.IsSlotReserved(InventorySlots.GetSlotIdFromString("weaponBayonetAK")))
			return false;
		
		if ( parent.FindAttachmentBySlotName("suppressorImpro") == NULL && parent.FindAttachmentBySlotName("weaponBayonetAK") == NULL )
		{
			return true;
		}
		return false;
	}
}