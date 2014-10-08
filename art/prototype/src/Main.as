package src
{
	// Copyright: (c) SteelCat 2009 - 2010
	import flash.display.MovieClip;
	import flash.text.TextField;
  	import flash.events.*;
	import src.Node;
	
	public class Main extends MovieClip
	{
		public var debug = false;
		public var firstTime = true;
		public var keyArray:Array = new Array();
		public var i:int;
		public var node:Array = new Array();
		public var bridge:Array = new Array();
		public var currNode:Node=node[0];
		public var currUINode:Node=node[0];
		public var prevNode:Node=node[0];
		public var currUnit:scout;
		public var nodeType:Class;
		public var objectType;
		public var nodeEvent:Node;
		public var _txtNodeDetails:TextField;
		public var currX:int;
		public var currY:int;
		public var doubleClick:int = 0;
		public var battleView:Boolean=true;
		
		public function Main() 
		{
			if(firstTime){firstTime = false; init();}
			
			stage.addEventListener(MouseEvent.CLICK, clickHandler);
			stage.addEventListener(MouseEvent.MOUSE_MOVE, dragHandler);
			stage.addEventListener(KeyboardEvent.KEY_DOWN,checkKeysDown);
			stage.addEventListener(KeyboardEvent.KEY_UP,checkKeysUp);
			stage.addEventListener(Event.ENTER_FRAME,UpdateScreen);
			
			//game.playerStartNode_mc.hideInstance();
			//game.playerStartNode_mc.tileSet[0][1].delete;
			
			_txtNodeDetails = this.nodeDetails_txt;
			
		}
		
		function init():void
		{			
			for( i=0; i<222; i++ )
			{
				keyArray.push([i,false]);
			}
			node[0]=game.playerNode;
			node[1]=game.enemyNode;
			node[2]=game.node01;
			node[3]=game.node02;
			node[4]=game.node03;
			node[5]=game.node04;
			node[6]=game.node05;
			node[7]=game.node06;
			node[8]=game.node07;
			node[9]=game.node08;
			
			bridge[0]=game.bridge01;
			bridge[1]=game.bridge02;
			bridge[2]=game.bridge03;
			bridge[3]=game.bridge04;
			bridge[4]=game.bridge05;
			bridge[5]=game.bridge06;
			bridge[6]=game.bridge07;
			bridge[7]=game.bridge08;
			bridge[8]=game.bridge09;
			bridge[9]=game.bridge10;
			bridge[10]=game.bridge11;
			bridge[11]=game.bridge12;
			bridge[12]=game.bridge13;
			
			//node[0].gotoAndStop('node');
			node[0].nodeName = "Player-Network";
			
			//node[1].gotoAndStop('node');
			node[1].nodeName = "Player-Network";
			
			//node[2].gotoAndStop('isp');
			node[2].nodeName = "node01";

			//node[3].gotoAndStop('isp');
			node[3].nodeName = "node02";
			
			//node[4].gotoAndStop('isp');
			node[4].nodeName = "node03";
			instanceView();
		}

		function checkKeysDown(event:KeyboardEvent):void
		{
			keyArray[event.keyCode][1]=true;
		}

		function checkKeysUp(event:KeyboardEvent):void
		{
			keyArray[event.keyCode][1]=false;
			if(debug){trace("Keycode pressed: " + event.keyCode);}
		}

		function isKeyDown(X)
		{
			return keyArray[X][1];
		}

		function UpdateScreen(event:Event):void
		{
			if(isKeyDown(37)==true){leftPress_mc.visible=true;}
				else{leftPress_mc.visible=false;}
			if(isKeyDown(39)==true){rightPress_mc.visible=true;}
				else{rightPress_mc.visible=false;}
			if(isKeyDown(38)==true){upPress_mc.visible=true;}
				else{upPress_mc.visible=false;}
			if(isKeyDown(40)==true){downPress_mc.visible=true;}
				else{downPress_mc.visible=false;}
			if(isKeyDown(65)==true){aPress_mc.visible=true;}
				else{aPress_mc.visible=false;}
			if(isKeyDown(83)==true){bPress_mc.visible=true;}
				else{bPress_mc.visible=false;}
			if(isKeyDown(68)==true){xPress_mc.visible=true;}
				else{xPress_mc.visible=false;}
			if(isKeyDown(70)==true){yPress_mc.visible=true;}
				else{yPress_mc.visible=false;}
			if(isKeyDown(13)==true){startPress_mc.visible=true;}
				else{startPress_mc.visible=false;}
			if(isKeyDown(16)==true){selectPress_mc.visible=true;}
				else{selectPress_mc.visible=false;}
			//if( view )
			//{
				//game.playerStartNode_mc.visible = false;
				//game.ispNode01_mc.visible = false;
				//game.ispNode02_mc.visible = false;
				//game.ispNode03_mc.visible = false;
				//game.currNode.visible=true;				
			//}
		}


		function clickHandler(event:MouseEvent):void 
		{
			// Check the currently selected object to find out if it has a Node
			// class attached. If so, the current Node selected will be changed.			
			if( Object(event.target) == exitInstance )
			{
				objectType = Object(event.target);
			}
			nodeType = Object(event.target).constructor;
			
			
			if( nodeType == Node )
			{
				nodeEvent = Node(event.target);
				if( nodeEvent == game.playerNode )
				{
					currUINode=ui.playerNode;
				}else if( nodeEvent == game.enemyNode )
				{
					currUINode=ui.enemyNode;
				}else if( nodeEvent == game.node01 )
				{
					currUINode=ui.node01;
				}else if( nodeEvent == game.node02 )
				{
					currUINode=ui.node02;
				}else if( nodeEvent == game.node03 )
				{
					currUINode=ui.node03;
				}else if( nodeEvent == game.node04 )
				{
					currUINode=ui.node04;
				}else if( nodeEvent == game.node05 )
				{
					currUINode=ui.node05;
				}else if( nodeEvent == game.node06 )
				{
					currUINode=ui.node06;
				}else if( nodeEvent == game.node07 )
				{
					currUINode=ui.node07;
				}else if( nodeEvent == game.node08 )
				{
					currUINode=ui.node08;
				}
			}
			if(debug){trace("Battle View: " + battleView);}
			//trace(currNode.nodeName, prevNode.nodeName);
			instanceView();
		}
		
		function dragHandler(event:MouseEvent):void
		{
			if ( mouseX>146 && mouseX<404 && mouseY>334 && mouseY<528 && event.buttonDown )
			{
				game.x -= (currX - mouseX );
				if( !battleView )
				{
					game.y -= (currY - mouseY);
				}else
				{
					game.z += (currY - mouseY);
				}
			}
			currX = mouseX;
			currY = mouseY;
		}
		
		public function nodeSelected(currNode):void
		{
			displayNodeProperties(_txtNodeDetails);
		}
		
		public function displayNodeProperties(textField:TextField):void
		{
			if(currNode != null)
			{
				textField.text = currNode.getNodeProperties();
				if(debug){trace("Curr node: " + currNode.nodeName);}
				game.currSelect.x = currNode.x;
				game.currSelect.y = currNode.y;
				game.currSelect.z = currNode.z;
				ui.currSelect.x = currUINode.x;
				ui.currSelect.y = currUINode.y;
				ui.currSelect.z = currUINode.z;
			}else{
				textField.text = "";
				if(debug){trace("Curr node: Nothing selected.");}
			}
		}
		
		public function instanceView()
		{
			if( !battleView )
			{
				if( nodeType == Node )
				{
					prevNode = currNode;
					currNode = nodeEvent;
					nodeSelected(currNode);
					if( currNode == prevNode )
					{
						currNode.addInstance();
						battleView = true;
						game.x =  game.x-mouseX+285;
						game.y =  game.y-mouseY+430+30;
						if(debug){trace("mouseX:", mouseX, "mouseY:", mouseY);}
					}
				}
				
				for( i=0; i<10; i++ )
				{
					node[i].visible = true;
				}
				for( i=0; i<13; i++ )
				{
					bridge[i].visible = true;
				}
				ui.playerNode.visible=false;
				ui.enemyNode.visible=false;
				ui.node01.visible=false;
				ui.node02.visible=false;
				ui.node03.visible=false;
				ui.node04.visible=false;
				ui.node05.visible=false;
				ui.node06.visible=false;
				ui.node07.visible=false;
				ui.node08.visible=false;
				ui.gotoAndStop('overview');
				ui.currSelect.visible = false;
				game.currSelect.visible = true;
				exitInstance.visible = false;
				trace("2");
			}
			if( battleView )
			{
				ui.currSelect.visible = false;
				ui.playerNode.visible=true;
				ui.enemyNode.visible=true;
				ui.node01.visible=true;
				ui.node02.visible=true;
				ui.node03.visible=true;
				ui.node04.visible=true;
				ui.node05.visible=true;
				ui.node06.visible=true;
				ui.node07.visible=true;
				ui.node08.visible=true;
				ui.gotoAndStop('battleview');
				ui.currSelect.visible = true;
				game.currSelect.visible = false;
				exitInstance.visible = true;
				for( i=0; i<10; i++ )
				{
					node[i].visible = false;
				}
				for( i=0; i<13; i++ )
				{
					bridge[i].visible = false;
				}
				//if( currNode!=null && prevNode!=null )
				//{
					currNode = node[0];
					currNode.addInstance();
					currNode.visible = true;
					//if( objectType == exitInstance )
					//{
						//currNode.removeInstance();
						//prevNode = null;
						//currNode = null;
						//objectType = null;
						//battleView = false;
						//game.z = -1.149;
						//instanceView();
					//}					
				//}
			}
		}
	}
}