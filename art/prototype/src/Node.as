package src
{
	// Copyright: (c) SteelCat 2009 - 2010
	import flash.display.MovieClip;

	public class Node extends MovieClip
    {
		public var nodeName:String; // Network name
		public var gridSize:Number = 12;
		public var i:Number;
		public var j:Number;
		public var tileSet:Array = new Array(gridSize);
		public var unit:Array = new Array(4); 
		
        public function Node() 
        {
			nodeName = "Default-Node";
        }

		public function getNodeProperties():String 
		{
			return nodeName;
		}
		
		public function addInstance()
		{
			for( i=0; i<18; i++ )
			{
				tileSet[i] = new Array(gridSize);
				for( j=0; j<gridSize; j++ )
				{
					tileSet[i][j] = new tile();
					tileSet[i][j].x = -350+i*40;
					tileSet[i][j].z = -50+j*40;
					tileSet[i][j].rotationX = -90;
					addChild(tileSet[i][j]);
				}
			}
			unit[0] = new scout();
			unit[0].z+=20;
			unit[0].x+=120;
			addChild(unit[0]);
		}
		
		public function removeInstance()
		{
			for( i=0; i<18; i++ )
			{
				for( j=0; j<gridSize; j++ )
				{
					removeChild(tileSet[i][j]);
				}
			}
			removeChild(unit[0]);
		}
    }
		
}