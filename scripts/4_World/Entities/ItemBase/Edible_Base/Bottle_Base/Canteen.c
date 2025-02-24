class Canteen extends Bottle_Base
{
	void Canteen()
	{

	}
	
	void ~Canteen()
	{
		
	}
	
	override bool IsContainer()
	{
		return true;
	}
	
	override string GetPouringSoundset()
	{
		return "emptyVessle_Canteen_SoundSet";
	}
	
		override string GetEmptyingLoopSoundsetHard()
	{
		return "pour_HardGround_Canteen_SoundSet";
	}
	
	override string GetEmptyingLoopSoundsetSoft()
	{
		return "pour_SoftGround_Canteen_SoundSet";
	}
	
	override string GetEmptyingLoopSoundsetWater()
	{
		return "pour_Water_Canteen_SoundSet";
	}
	
	override string GetEmptyingEndSoundsetHard()
	{
		return "pour_End_HardGround_Canteen_SoundSet";
	}
	
	override string GetEmptyingEndSoundsetSoft()
	{
		return "pour_End_SoftGround_Canteen_SoundSet";
	}
	
	override string GetEmptyingEndSoundsetWater()
	{
		return "pour_End_Water_Canteen_SoundSet";
	}
	
	override bool CanPutInCargo( EntityAI parent )
	{
		if ( !super.CanPutInCargo(parent) ) {return false;}	
		if ( !(parent.IsKindOf("Canteen"))/* && !(parent.IsKindOf("Container_Base"))*/)
		{
			return true;
		}
		
		return false;
	}
	
	override bool IsOpen()
	{
		return true;
	}
	
	override void EEOnCECreate()
	{
		int rand = Math.RandomInt(0, 10);
		if (rand > 5)
		{
			InsertAgent(eAgents.CHOLERA, 1);
		}
	}
}