#ifdef __WAND__

dependency[
	window.o
]
target[
	name[
		window.h
	]
	type[
		include
	]
]
#endif

#ifndef guard_Window_H
#define guard_Window_H

#include <vector/vector2d.h>
#include <herbs/chartype/chartype.h>
#include <herbs/string/string.h>
#include <cstddef>

namespace Gui
	{
	class Gui;
	class Font;
	
	/**Base class for a Window.
	\nosubgrouping
	*/
	class Window
		{
		friend class Dialog;
		public:
			Window(const Window&)=delete;
			void operator=(const Window&)=delete;
			Window(Window&&)=delete;
			void operator=(Window&&)=delete;
			
			Window(Gui& gui_obj,const charsys_t* classname,uint32_t style_0
				,uint32_t style_1,Window* parent);
			
			virtual ~Window();
			
			/**\name Window identification*/
			
			/**{*/
			
			/**Sets window id.
			*/
			void idSet(uint32_t id_new);
			
			/**Retrievs the window id.
			*/
			uint32_t idGet() const;
			
			/**}*/
			
			/**\name Window text properties.
			*/
			
			/**{*/
			
			/**Sets the window title or text if appliciable.
			*/			
			virtual void titleSet(const char_t* title);
			
			/**Retrievs the window title or text if appliciable.
			*/
			virtual Herbs::String titleGet() const;
			
			/**Request the window change its font.
			*/
			virtual void fontChangeRequest(const Font& font);
			
			/**Retrievs the size of the redered line.
			*/
			Vector::Vector2d<int> sizeLine(const char_t* line) const;
			
			/**Retrievs the size of the redered line.
			*/
			Vector::Vector2d<int> sizeLine(const Herbs::String& line) const;
			
			/**Retrievs the size of the currently displayed content.
			*/
			virtual Vector::Vector2d<int> sizeContent() const;
			/**}*/

				
			
			/**\name Window geometry*/
			
			/**{*/
			
			/**Moves the window using absolute (pixel) coordinates.
			* \param anchor sets the coordinate of the window used for positioning.
			*        For more details, see figure $ref("window_coordfig").
			* \param position sets where in its parent window the point at anchor
			*        ends up. For more details, see figure $ref("window_coordfig").
			*/
			void moveAbsolute(Vector::Vector2d<float> anchor,Vector::Vector2d<float> position);
			
			/**Moves the window using coordinates relative to the size of its
			* parent window.
			* \param anchor sets the coordinate of the window used for positioning.
			*        For more details, see figure $ref("window_coordfig").
			* \param position sets where in its parent window the point at anchor
			*        ends up. For more details, see figure $ref("window_coordfig").
			*/			
			void moveRelative(Vector::Vector2d<float> anchor,Vector::Vector2d<float> position);
			
			/**Sets the window size in pixels.
			*/
			void sizeAbsolute(int width, int height);
			
			/**Sets the window size relative to its parent.
			*/
			void sizeRelative(float width, float height);
			
			/**Retrievs the size of the client area.
			*/
			Vector::Vector2d<int> sizeClientGet() const;
			
			static Vector::Vector2d<int> sizeClientFromParam1(size_t param_1);
			
			/**Retrievs the full size of the window.
			*/
			Vector::Vector2d<int> sizeWindowGet() const;
			
			/**}*/
			
			
			/**\name Window appearance*/
			
			/**{*/
			
			/**Shows the window.
			*/
			void show(int options);
			
			static const int DisplayHide=0;
			static const int DisplayShownormal=1;
			static const int DisplayNormal=1;
			static const int DisplayShowminimized=2;
			static const int DisplayShowmaximized=3;
			static const int DisplayMaximize=3;
			static const int DisplayShownoactivate=4;
			static const int DisplayShow=5;
			static const int DisplayMinimize=6;
			static const int DisplayShowminnoactive=7;
			static const int DisplayShowna=8;
			static const int DisplayRestore=9;
			static const int DisplayShowdefault=10;
			static const int DisplayForceminimize=11;
			static const int DisplayMax=11;
			static const int DisplayParentclosing=1;
			static const int DisplayOtherzoom=2;
			static const int DisplayParentopening=3;
			static const int DisplayOtherunzoom=4;
			
			
			/**Sets a new window style.
			*/
			void styleSet(uint32_t style_0,uint32_t style_1);
			
			/**Gets the current window style.
			*/
			uint32_t styleGet(size_t set) const;
			
			/**Makes the window a popup window.
			*/
			void popup();
			
			/**Enables or disables the window.
			*/
			void enable(bool status);
			
			///*Styles
			static const uint32_t StyleEx_dlgmodalframe=0x00000001;
			static const uint32_t StyleEx_noparentnotify=0x00000004;
			static const uint32_t StyleEx_topmost=0x00000008;
			static const uint32_t StyleEx_acceptfiles=0x00000010;
			static const uint32_t StyleEx_transparent=0x00000020;
			static const uint32_t StyleEx_mdichild=0x00000040;
			static const uint32_t StyleEx_toolwindow=0x00000080;
			static const uint32_t StyleEx_windowedge=0x00000100;
			static const uint32_t StyleEx_clientedge=0x00000200;
			static const uint32_t StyleEx_contexthelp=0x00000400;
			static const uint32_t StyleEx_right=0x00001000;
			static const uint32_t StyleEx_left=0x00000000;
			static const uint32_t StyleEx_rtlreading=0x00002000;
			static const uint32_t StyleEx_ltrreading=0x00000000;
			static const uint32_t StyleEx_leftscrollbar=0x00004000;
			static const uint32_t StyleEx_rightscrollbar=0x00000000;
			static const uint32_t StyleEx_controlparent=0x00010000;
			static const uint32_t StyleEx_staticedge=0x00020000;
			static const uint32_t StyleEx_appwindow=0x00040000;
			static const uint32_t StyleEx_noinheritlayout=0x00100000;
			static const uint32_t StyleEx_layoutrtl=0x00400000;
			static const uint32_t StyleEx_composited=0x02000000;
			static const uint32_t StyleEx_noactivate=0x08000000;
			
			static const uint32_t StyleOverlapped=0x00000000;
			static const uint32_t StylePopup=0x80000000;
			static const uint32_t StyleChild=0x40000000;
			static const uint32_t StyleMinimize=0x20000000;
			static const uint32_t StyleVisible=0x10000000;
			static const uint32_t StyleDisabled=0x08000000;
			static const uint32_t StyleClipsiblings=0x04000000;
			static const uint32_t StyleClipchildren=0x02000000;
			static const uint32_t StyleMaximize=0x01000000;
			static const uint32_t StyleCaption=0x00c00000;
			static const uint32_t StyleBorder=0x00800000;
			static const uint32_t StyleDlgframe=0x00400000;
			static const uint32_t StyleVscroll=0x00200000;
			static const uint32_t StyleHscroll=0x00100000;
			static const uint32_t StyleSysmenu=0x00080000;
			static const uint32_t StyleThickframe=0x00040000;
			static const uint32_t StyleGroup=0x00020000;
			static const uint32_t StyleTabstop=0x00010000;
			static const uint32_t StyleMinimizebox=0x00020000;
			static const uint32_t StyleMaximizebox=0x00010000;
			
			/**}*/
			
			/**\name Communication*/
			
			/**{*/
			
			/**This method is called when an GUI event occurs.
			*/
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1)=0;
			
			/**This method is called when the Window should update the value of any
			associated data.
			*/
			virtual void valueUpdate(){}
			
			/**This method is called when the Window should update its view of any
			associated data.
			*/
			virtual void displayUpdate(){}
			

			
			///*Messages
			static unsigned int const MessageNull=0x0000;
			static unsigned int const MessageCreate=0x0001;
			static unsigned int const MessageDestroy=0x0002;
			static unsigned int const MessageMove=0x0003;
			static unsigned int const MessageSize=0x0005;
			static unsigned int const MessageActivate=0x0006;
			static unsigned int const MessageSetfocus=0x0007;
			static unsigned int const MessageKillfocus=0x0008;
			static unsigned int const MessageEnable=0x000a;
			static unsigned int const MessageSetredraw=0x000b;
			static unsigned int const MessageSettext=0x000c;
			static unsigned int const MessageGettext=0x000d;
			static unsigned int const MessageGettextlength=0x000e;
			static unsigned int const MessagePaint=0x000f;
			static unsigned int const MessageClose=0x0010;
			static unsigned int const MessageQueryendsession=0x0011;
			static unsigned int const MessageQueryopen=0x0013;
			static unsigned int const MessageEndsession=0x0016;
			static unsigned int const MessageQuit=0x0012;
			static unsigned int const MessageErasebkgnd=0x0014;
			static unsigned int const MessageSyscolorchange=0x0015;
			static unsigned int const MessageShowwindow=0x0018;
			static unsigned int const MessageWininichange=0x001a;
			static unsigned int const MessageDevmodechange=0x001b;
			static unsigned int const MessageActivateapp=0x001c;
			static unsigned int const MessageFontchange=0x001d;
			static unsigned int const MessageTimechange=0x001e;
			static unsigned int const MessageCancelmode=0x001f;
			static unsigned int const MessageSetcursor=0x0020;
			static unsigned int const MessageMouseactivate=0x0021;
			static unsigned int const MessageChildactivate=0x0022;
			static unsigned int const MessageQueuesync=0x0023;
			static unsigned int const MessageGetminmaxinfo=0x0024;
			static unsigned int const MessagePainticon=0x0026;
			static unsigned int const MessageIconerasebkgnd=0x0027;
			static unsigned int const MessageNextdlgctl=0x0028;
			static unsigned int const MessageSpoolerstatus=0x002a;
			static unsigned int const MessageDrawitem=0x002b;
			static unsigned int const MessageMeasureitem=0x002c;
			static unsigned int const MessageDeleteitem=0x002d;
			static unsigned int const MessageVkeytoitem=0x002e;
			static unsigned int const MessageChartoitem=0x002f;
			static unsigned int const MessageSetfont=0x0030;
			static unsigned int const MessageGetfont=0x0031;
			static unsigned int const MessageSethotkey=0x0032;
			static unsigned int const MessageGethotkey=0x0033;
			static unsigned int const MessageQuerydragicon=0x0037;
			static unsigned int const MessageCompareitem=0x0039;
			static unsigned int const MessageGetobject=0x003d;
			static unsigned int const MessageCompacting=0x0041;
			static unsigned int const MessageCommnotify=0x0044;
			static unsigned int const MessageWindowposchanging=0x0046;
			static unsigned int const MessageWindowposchanged=0x0047;
			static unsigned int const MessagePower=0x0048;
			static unsigned int const MessageCopydata=0x004a;
			static unsigned int const MessageCanceljournal=0x004b;
			static unsigned int const MessageNotify=0x004e;
			static unsigned int const MessageInputlangchangerequest=0x0050;
			static unsigned int const MessageInputlangchange=0x0051;
			static unsigned int const MessageTcard=0x0052;
			static unsigned int const MessageHelp=0x0053;
			static unsigned int const MessageUserchanged=0x0054;
			static unsigned int const MessageNotifyformat=0x0055;
			static unsigned int const MessageContextmenu=0x007b;
			static unsigned int const MessageStylechanging=0x007c;
			static unsigned int const MessageStylechanged=0x007d;
			static unsigned int const MessageDisplaychange=0x007e;
			static unsigned int const MessageGeticon=0x007f;
			static unsigned int const MessageSeticon=0x0080;
			static unsigned int const MessageNccreate=0x0081;
			static unsigned int const MessageNcdestroy=0x0082;
			static unsigned int const MessageNccalcsize=0x0083;
			static unsigned int const MessageNchittest=0x0084;
			static unsigned int const MessageNcpaint=0x0085;
			static unsigned int const MessageNcactivate=0x0086;
			static unsigned int const MessageGetdlgcode=0x0087;
			static unsigned int const MessageSyncpaint=0x0088;
			static unsigned int const MessageNcmousemove=0x00a0;
			static unsigned int const MessageNclbuttondown=0x00a1;
			static unsigned int const MessageNclbuttonup=0x00a2;
			static unsigned int const MessageNclbuttondblclk=0x00a3;
			static unsigned int const MessageNcrbuttondown=0x00a4;
			static unsigned int const MessageNcrbuttonup=0x00a5;
			static unsigned int const MessageNcrbuttondblclk=0x00a6;
			static unsigned int const MessageNcmbuttondown=0x00a7;
			static unsigned int const MessageNcmbuttonup=0x00a8;
			static unsigned int const MessageNcmbuttondblclk=0x00a9;
			static unsigned int const MessageNcxbuttondown=0x00ab;
			static unsigned int const MessageNcxbuttonup=0x00ac;
			static unsigned int const MessageNcxbuttondblclk=0x00ad;
			static unsigned int const MessageInput=0x00ff;
			static unsigned int const MessageKeyfirst=0x0100;
			static unsigned int const MessageKeydown=0x0100;
			static unsigned int const MessageKeyup=0x0101;
			static unsigned int const MessageChar=0x0102;
			static unsigned int const MessageDeadchar=0x0103;
			static unsigned int const MessageSyskeydown=0x0104;
			static unsigned int const MessageSyskeyup=0x0105;
			static unsigned int const MessageSyschar=0x0106;
			static unsigned int const MessageSysdeadchar=0x0107;
			static unsigned int const MessageUnichar=0x0109;
			static unsigned int const MessageKeylast=0x0109;
			static unsigned int const MessageIme_startcomposition=0x010d;
			static unsigned int const MessageIme_endcomposition=0x010e;
			static unsigned int const MessageIme_composition=0x010f;
			static unsigned int const MessageIme_keylast=0x010f;
			static unsigned int const MessageInitdialog=0x0110;
			static unsigned int const MessageCommand=0x0111;
			static unsigned int const MessageSyscommand=0x0112;
			static unsigned int const MessageTimer=0x0113;
			static unsigned int const MessageHscroll=0x0114;
			static unsigned int const MessageVscroll=0x0115;
			static unsigned int const MessageInitmenu=0x0116;
			static unsigned int const MessageInitmenupopup=0x0117;
			static unsigned int const MessageMenuselect=0x011f;
			static unsigned int const MessageGesture=0x0119;
			static unsigned int const MessageGesturenotify=0x011a;
			static unsigned int const MessageMenuchar=0x0120;
			static unsigned int const MessageEnteridle=0x0121;
			static unsigned int const MessageMenurbuttonup=0x0122;
			static unsigned int const MessageMenudrag=0x0123;
			static unsigned int const MessageMenugetobject=0x0124;
			static unsigned int const MessageUninitmenupopup=0x0125;
			static unsigned int const MessageMenucommand=0x0126;
			static unsigned int const MessageChangeuistate=0x0127;
			static unsigned int const MessageUpdateuistate=0x0128;
			static unsigned int const MessageQueryuistate=0x0129;
			static unsigned int const MessageCtlcolormsgbox=0x0132;
			static unsigned int const MessageCtlcoloredit=0x0133;
			static unsigned int const MessageCtlcolorlistbox=0x0134;
			static unsigned int const MessageCtlcolorbtn=0x0135;
			static unsigned int const MessageCtlcolordlg=0x0136;
			static unsigned int const MessageCtlcolorscrollbar=0x0137;
			static unsigned int const MessageCtlcolorstatic=0x0138;
			static unsigned int const MessageMousefirst=0x0200;
			static unsigned int const MessageMousemove=0x0200;
			static unsigned int const MessageLbuttondown=0x0201;
			static unsigned int const MessageLbuttonup=0x0202;
			static unsigned int const MessageLbuttondblclk=0x0203;
			static unsigned int const MessageRbuttondown=0x0204;
			static unsigned int const MessageRbuttonup=0x0205;
			static unsigned int const MessageRbuttondblclk=0x0206;
			static unsigned int const MessageMbuttondown=0x0207;
			static unsigned int const MessageMbuttonup=0x0208;
			static unsigned int const MessageMbuttondblclk=0x0209;
			static unsigned int const MessageMousewheel=0x020a;
			static unsigned int const MessageXbuttondown=0x020b;
			static unsigned int const MessageXbuttonup=0x020c;
			static unsigned int const MessageXbuttondblclk=0x020d;
			static unsigned int const MessageMouselast=0x020d;
			static unsigned int const MessageMousehwheel=0x020e;
			static unsigned int const MessageParentnotify=0x0210;
			static unsigned int const MessageEntermenuloop=0x0211;
			static unsigned int const MessageExitmenuloop=0x0212;
			static unsigned int const MessageNextmenu=0x0213;
			static unsigned int const MessageSizing=0x0214;
			static unsigned int const MessageCapturechanged=0x0215;
			static unsigned int const MessageMoving=0x0216;
			static unsigned int const MessagePowerbroadcast=0x0218;
			static unsigned int const MessageDevicechange=0x0219;
			static unsigned int const MessageMdicreate=0x0220;
			static unsigned int const MessageMdidestroy=0x0221;
			static unsigned int const MessageMdiactivate=0x0222;
			static unsigned int const MessageMdirestore=0x0223;
			static unsigned int const MessageMdinext=0x0224;
			static unsigned int const MessageMdimaximize=0x0225;
			static unsigned int const MessageMditile=0x0226;
			static unsigned int const MessageMdicascade=0x0227;
			static unsigned int const MessageMdiiconarrange=0x0228;
			static unsigned int const MessageMdigetactive=0x0229;
			static unsigned int const MessageMdisetmenu=0x0230;
			static unsigned int const MessageEntersizemove=0x0231;
			static unsigned int const MessageExitsizemove=0x0232;
			static unsigned int const MessageDropfiles=0x0233;
			static unsigned int const MessageMdirefreshmenu=0x0234;
			static unsigned int const MessageIme_setcontext=0x0281;
			static unsigned int const MessageIme_notify=0x0282;
			static unsigned int const MessageIme_control=0x0283;
			static unsigned int const MessageIme_compositionfull=0x0284;
			static unsigned int const MessageIme_select=0x0285;
			static unsigned int const MessageIme_char=0x0286;
			static unsigned int const MessageIme_request=0x0288;
			static unsigned int const MessageIme_keydown=0x0290;
			static unsigned int const MessageIme_keyup=0x0291;
			static unsigned int const MessageMousehover=0x02a1;
			static unsigned int const MessageMouseleave=0x02a3;
			static unsigned int const MessageNcmousehover=0x02a0;
			static unsigned int const MessageNcmouseleave=0x02a2;
			static unsigned int const MessageWtssession_change=0x02b1;
			static unsigned int const MessageTablet_first=0x02c0;
			static unsigned int const MessageTablet_last=0x02df;
			static unsigned int const MessageCut=0x0300;
			static unsigned int const MessageCopy=0x0301;
			static unsigned int const MessagePaste=0x0302;
			static unsigned int const MessageClear=0x0303;
			static unsigned int const MessageUndo=0x0304;
			static unsigned int const MessageRenderformat=0x0305;
			static unsigned int const MessageRenderallformats=0x0306;
			static unsigned int const MessageDestroyclipboard=0x0307;
			static unsigned int const MessageDrawclipboard=0x0308;
			static unsigned int const MessagePaintclipboard=0x0309;
			static unsigned int const MessageVscrollclipboard=0x030a;
			static unsigned int const MessageSizeclipboard=0x030b;
			static unsigned int const MessageAskcbformatname=0x030c;
			static unsigned int const MessageChangecbchain=0x030d;
			static unsigned int const MessageHscrollclipboard=0x030e;
			static unsigned int const MessageQuerynewpalette=0x030f;
			static unsigned int const MessagePaletteischanging=0x0310;
			static unsigned int const MessagePalettechanged=0x0311;
			static unsigned int const MessageHotkey=0x0312;
			static unsigned int const MessagePrint=0x0317;
			static unsigned int const MessagePrintclient=0x0318;
			static unsigned int const MessageAppcommand=0x0319;
			static unsigned int const MessageThemechanged=0x031a;
			static unsigned int const MessageHandheldfirst=0x0358;
			static unsigned int const MessageHandheldlast=0x035f;
			static unsigned int const MessageAfxfirst=0x0360;
			static unsigned int const MessageAfxlast=0x037f;
			static unsigned int const MessagePenwinfirst=0x0380;
			static unsigned int const MessagePenwinlast=0x038f;
			static unsigned int const MessageApp=0x8000;
			static unsigned int const MessageUser=0x0400;
			static unsigned int const MessageTouchmove=576;
			static unsigned int const MessageTouchdown=577;
			static unsigned int const MessageTouchup=578;
			
			/**}*/
	
			/**Returns the a pointer to the corresponding Window given a system
			* handle win.
			*/
			static Window* objectGet(void* win);
			
			Gui& hostGet() const
				{return m_gui;}
	
		protected:
				
			/**Returns the system handle to the Window given by win.
			*/
			static void* handleGet(Window* win);
			
			Gui& m_gui;
			void* handle;
		};
	}

#endif
