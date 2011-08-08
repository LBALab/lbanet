/* -*-c++-*- OpenSceneGraph - Copyright (C) 2009 Wang Rui
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/

#include "GraphicsWindowQt"


//////////////////////////////////////////////////////////////////////////////
//                       Keyboard key mapping for Qt
//////////////////////////////////////////////////////////////////////////////

class QtKeyboardMap
{
    public:

        QtKeyboardMap()
        {
			_keyMap[Qt::Key_Backspace] = osgGA::GUIEventAdapter::KEY_BackSpace;
			_keyMap[Qt::Key_Tab] = osgGA::GUIEventAdapter::KEY_Tab;
			_keyMap[Qt::Key_Clear] = osgGA::GUIEventAdapter::KEY_Clear;
			_keyMap[Qt::Key_Return] = osgGA::GUIEventAdapter::KEY_Return;
			_keyMap[Qt::Key_Pause] = osgGA::GUIEventAdapter::KEY_Pause;
			_keyMap[Qt::Key_ScrollLock] = osgGA::GUIEventAdapter::KEY_Scroll_Lock;
			_keyMap[Qt::Key_SysReq] = osgGA::GUIEventAdapter::KEY_Sys_Req;
			_keyMap[Qt::Key_Escape] = osgGA::GUIEventAdapter::KEY_Escape;
			_keyMap[Qt::Key_Delete] = osgGA::GUIEventAdapter::KEY_Delete;

			_keyMap[Qt::Key_Home] = osgGA::GUIEventAdapter::KEY_Home;
			_keyMap[Qt::Key_Left] = osgGA::GUIEventAdapter::KEY_Left;
			_keyMap[Qt::Key_Up] = osgGA::GUIEventAdapter::KEY_Up;
			_keyMap[Qt::Key_Right] = osgGA::GUIEventAdapter::KEY_Right;
			_keyMap[Qt::Key_Down] = osgGA::GUIEventAdapter::KEY_Down;
			_keyMap[Qt::Key_PageUp] = osgGA::GUIEventAdapter::KEY_Page_Up;
			_keyMap[Qt::Key_PageDown] = osgGA::GUIEventAdapter::KEY_Page_Down;
			_keyMap[Qt::Key_End] = osgGA::GUIEventAdapter::KEY_End;

			_keyMap[Qt::Key_Select] = osgGA::GUIEventAdapter::KEY_Select;
			_keyMap[Qt::Key_Print] = osgGA::GUIEventAdapter::KEY_Print;
			_keyMap[Qt::Key_Execute] = osgGA::GUIEventAdapter::KEY_Execute;
			_keyMap[Qt::Key_Insert] = osgGA::GUIEventAdapter::KEY_Insert;
			_keyMap[Qt::Key_Menu] = osgGA::GUIEventAdapter::KEY_Menu;
			_keyMap[Qt::Key_Cancel] = osgGA::GUIEventAdapter::KEY_Cancel;
			_keyMap[Qt::Key_Help] = osgGA::GUIEventAdapter::KEY_Help;
			_keyMap[Qt::Key_Mode_switch] = osgGA::GUIEventAdapter::KEY_Mode_switch;
			_keyMap[Qt::Key_NumLock] = osgGA::GUIEventAdapter::KEY_Num_Lock;

			_keyMap[Qt::Key_Shift] = osgGA::GUIEventAdapter::KEY_Shift_L;
			_keyMap[Qt::Key_Shift] = osgGA::GUIEventAdapter::KEY_Shift_R;
			_keyMap[Qt::Key_Control] = osgGA::GUIEventAdapter::KEY_Control_L;
			_keyMap[Qt::Key_Control] = osgGA::GUIEventAdapter::KEY_Control_R;
			_keyMap[Qt::Key_CapsLock] = osgGA::GUIEventAdapter::KEY_Caps_Lock;
			_keyMap[Qt::Key_CapsLock] = osgGA::GUIEventAdapter::KEY_Shift_Lock;

			_keyMap[Qt::Key_Meta] = osgGA::GUIEventAdapter::KEY_Meta_R; // Qt doesn't have a Meta L
			_keyMap[Qt::Key_Alt] = osgGA::GUIEventAdapter::KEY_Alt_R; // Qt doesn't have a Alt L
			_keyMap[Qt::Key_Super_L] = osgGA::GUIEventAdapter::KEY_Super_L;
			_keyMap[Qt::Key_Super_R] = osgGA::GUIEventAdapter::KEY_Super_R;
			_keyMap[Qt::Key_Hyper_L] = osgGA::GUIEventAdapter::KEY_Hyper_L;
			_keyMap[Qt::Key_Hyper_R] = osgGA::GUIEventAdapter::KEY_Hyper_R;

			_keyMap[Qt::Key_Equal] = osgGA::GUIEventAdapter::KEY_KP_Equal;
			_keyMap[Qt::Key_Asterisk] = osgGA::GUIEventAdapter::KEY_KP_Multiply;
			_keyMap[Qt::Key_Plus] = osgGA::GUIEventAdapter::KEY_KP_Add;

			_keyMap[Qt::Key_Minus] = osgGA::GUIEventAdapter::KEY_KP_Subtract;
			_keyMap[Qt::Key_Period] = osgGA::GUIEventAdapter::KEY_KP_Decimal;
			_keyMap[Qt::Key_division] = osgGA::GUIEventAdapter::KEY_KP_Divide;
			_keyMap[Qt::Key_0] = osgGA::GUIEventAdapter::KEY_KP_0;
			_keyMap[Qt::Key_1] = osgGA::GUIEventAdapter::KEY_KP_1;
			_keyMap[Qt::Key_2] = osgGA::GUIEventAdapter::KEY_KP_2;
			_keyMap[Qt::Key_2] = osgGA::GUIEventAdapter::KEY_KP_3;
			_keyMap[Qt::Key_4] = osgGA::GUIEventAdapter::KEY_KP_4;
			_keyMap[Qt::Key_5] = osgGA::GUIEventAdapter::KEY_KP_5;
			_keyMap[Qt::Key_6] = osgGA::GUIEventAdapter::KEY_KP_6;
			_keyMap[Qt::Key_7] = osgGA::GUIEventAdapter::KEY_KP_7;
			_keyMap[Qt::Key_8] = osgGA::GUIEventAdapter::KEY_KP_8;
			_keyMap[Qt::Key_9] = osgGA::GUIEventAdapter::KEY_KP_9;

			_keyMap[Qt::Key_F1] = osgGA::GUIEventAdapter::KEY_F1;
			_keyMap[Qt::Key_F2] = osgGA::GUIEventAdapter::KEY_F2;
			_keyMap[Qt::Key_F3] = osgGA::GUIEventAdapter::KEY_F3;
			_keyMap[Qt::Key_F4] = osgGA::GUIEventAdapter::KEY_F4;
			_keyMap[Qt::Key_F5] = osgGA::GUIEventAdapter::KEY_F5;
			_keyMap[Qt::Key_F6] = osgGA::GUIEventAdapter::KEY_F6;
			_keyMap[Qt::Key_F7] = osgGA::GUIEventAdapter::KEY_F7;
			_keyMap[Qt::Key_F8] = osgGA::GUIEventAdapter::KEY_F8;
			_keyMap[Qt::Key_F9] = osgGA::GUIEventAdapter::KEY_F9;
			_keyMap[Qt::Key_F10] = osgGA::GUIEventAdapter::KEY_F10;
			_keyMap[Qt::Key_F11] = osgGA::GUIEventAdapter::KEY_F11;
			_keyMap[Qt::Key_F12] = osgGA::GUIEventAdapter::KEY_F12;
			_keyMap[Qt::Key_F13] = osgGA::GUIEventAdapter::KEY_F13;
			_keyMap[Qt::Key_F14] = osgGA::GUIEventAdapter::KEY_F14;
			_keyMap[Qt::Key_F15] = osgGA::GUIEventAdapter::KEY_F15;
			_keyMap[Qt::Key_F16] = osgGA::GUIEventAdapter::KEY_F16;
			_keyMap[Qt::Key_F17] = osgGA::GUIEventAdapter::KEY_F17;
			_keyMap[Qt::Key_F18] = osgGA::GUIEventAdapter::KEY_F18;
			_keyMap[Qt::Key_F19] = osgGA::GUIEventAdapter::KEY_F19;
			_keyMap[Qt::Key_F20] = osgGA::GUIEventAdapter::KEY_F20;
			_keyMap[Qt::Key_F21] = osgGA::GUIEventAdapter::KEY_F21;
			_keyMap[Qt::Key_F22] = osgGA::GUIEventAdapter::KEY_F22;
			_keyMap[Qt::Key_F23] = osgGA::GUIEventAdapter::KEY_F23;
			_keyMap[Qt::Key_F24] = osgGA::GUIEventAdapter::KEY_F24;
			_keyMap[Qt::Key_F25] = osgGA::GUIEventAdapter::KEY_F25;
			_keyMap[Qt::Key_F26] = osgGA::GUIEventAdapter::KEY_F26;
			_keyMap[Qt::Key_F27] = osgGA::GUIEventAdapter::KEY_F27;
			_keyMap[Qt::Key_F28] = osgGA::GUIEventAdapter::KEY_F28;
			_keyMap[Qt::Key_F29] = osgGA::GUIEventAdapter::KEY_F29;
			_keyMap[Qt::Key_F30] = osgGA::GUIEventAdapter::KEY_F30;
			_keyMap[Qt::Key_F31] = osgGA::GUIEventAdapter::KEY_F31;
			_keyMap[Qt::Key_F32] = osgGA::GUIEventAdapter::KEY_F32;
			_keyMap[Qt::Key_F33] = osgGA::GUIEventAdapter::KEY_F33;
			_keyMap[Qt::Key_F34] = osgGA::GUIEventAdapter::KEY_F34;
			_keyMap[Qt::Key_F35] = osgGA::GUIEventAdapter::KEY_F35;

			_keyMap[Qt::Key_Space] = osgGA::GUIEventAdapter::KEY_Space;
        }

        ~QtKeyboardMap() {}

        int remapKey(int key)
        {
            KeyMap::const_iterator map = _keyMap.find(key);
            return map==_keyMap.end() ? key : map->second;
        }

    protected:

        typedef std::map<int, int> KeyMap;
        KeyMap _keyMap;
};

static QtKeyboardMap s_qtKeyboardMap;
static int remapQtKey(int key)
{
    return s_qtKeyboardMap.remapKey(key);
}








GraphWidget::GraphWidget( const QGLFormat& format, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f )
: QGLWidget(format, parent, shareWidget, f), _handlekey(true)
{
    setAutoBufferSwap( false );
    setMouseTracking( true );
}

void GraphWidget::SetHandleKey(bool handlek)
{
	_handlekey = handlek;
}


void GraphWidget::setKeyboardModifiers( QInputEvent* event )
{
    int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
    unsigned int mask = 0;
    if ( modkey & Qt::ShiftModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
    if ( modkey & Qt::ControlModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
    if ( modkey & Qt::AltModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
    _gw->getEventQueue()->getCurrentEventState()->setModKeyMask( mask );
}

void GraphWidget::resizeEvent( QResizeEvent* event )
{
    const QSize& size = event->size();
    _gw->getEventQueue()->windowResize( 0, 0, size.width(), size.height() );
    _gw->resized( 0, 0, size.width(), size.height() );
}

void GraphWidget::keyPressEvent( QKeyEvent* event )
{
	if(_handlekey)
	{
		setKeyboardModifiers( event );
		int key = remapQtKey(event->key());
		int unicode = 0;
		QVector<uint> unicodev = event->text().toUcs4();
		if(unicodev.size() >= 1)
			unicode = (int)unicodev[0];
		_gw->getEventQueue()->keyPress( key, unicode);
	}
	else
		QWidget::keyPressEvent(event);
}

void GraphWidget::keyReleaseEvent( QKeyEvent* event )
{
	if(_handlekey)
	{
		setKeyboardModifiers( event );
		int key = remapQtKey(event->key());
		int unicode = 0;
		QVector<uint> unicodev = event->text().toUcs4();
		if(unicodev.size() >= 1)
			unicode = (int)unicodev[0];
		_gw->getEventQueue()->keyRelease( key, unicode);
	}
	else
		QWidget::keyPressEvent(event);
}

void GraphWidget::mousePressEvent( QMouseEvent* event )
{
    int button = 0;
    switch ( event->button() )
    {
        case Qt::LeftButton: button = 1; break;
        case Qt::MidButton: button = 2; break;
        case Qt::RightButton: button = 3; break;
        case Qt::NoButton: button = 0; break;
        default: button = 0; break;
    }
    setKeyboardModifiers( event );
    _gw->getEventQueue()->mouseButtonPress( event->x(), event->y(), button );
}

void GraphWidget::mouseReleaseEvent( QMouseEvent* event )
{
    int button = 0;
    switch ( event->button() )
    {
        case Qt::LeftButton: button = 1; break;
        case Qt::MidButton: button = 2; break;
        case Qt::RightButton: button = 3; break;
        case Qt::NoButton: button = 0; break;
        default: button = 0; break;
    }
    setKeyboardModifiers( event );
    _gw->getEventQueue()->mouseButtonRelease( event->x(), event->y(), button );
}

void GraphWidget::mouseDoubleClickEvent( QMouseEvent* event )
{
    int button = 0;
    switch ( event->button() )
    {
        case Qt::LeftButton: button = 1; break;
        case Qt::MidButton: button = 2; break;
        case Qt::RightButton: button = 3; break;
        case Qt::NoButton: button = 0; break;
        default: button = 0; break;
    }
    setKeyboardModifiers( event );
    _gw->getEventQueue()->mouseDoubleButtonPress( event->x(), event->y(), button );
}

void GraphWidget::mouseMoveEvent( QMouseEvent* event )
{
    setKeyboardModifiers( event );
    _gw->getEventQueue()->mouseMotion( event->x(), event->y() );
}

void GraphWidget::wheelEvent( QWheelEvent* event )
{
    setKeyboardModifiers( event );
    _gw->getEventQueue()->mouseScroll(
        event->delta()>0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN );
}

void GraphWidget::closeEvent( QCloseEvent* event )
{
	//_gw->getEventQueue()->quitApplication();
}



GraphicsWindowQt::GraphicsWindowQt( osg::GraphicsContext::Traits* traits)
:   _widget(0),
    _initialized(false),
    _realized(false)
{
    _traits = traits;
    _initialized = init();

    if ( valid() )
    {
        setState( new osg::State );
        getState()->setGraphicsContext(this);

        if ( _traits.valid() && _traits->sharedContext )
        {
            getState()->setContextID( _traits->sharedContext->getState()->getContextID() );
            incrementContextIDUsageCount( getState()->getContextID() );
        }
        else
        {
            getState()->setContextID( osg::GraphicsContext::createNewContextID() );
        }
    }
}

GraphicsWindowQt::~GraphicsWindowQt()
{
    close();
}

bool GraphicsWindowQt::init()
{
    QGLFormat format( QGLFormat::defaultFormat() );
    format.setAlphaBufferSize( _traits->alpha );
    format.setRedBufferSize( _traits->red );
    format.setGreenBufferSize( _traits->green );
    format.setBlueBufferSize( _traits->blue );
    format.setDepthBufferSize( _traits->depth );
    format.setStencilBufferSize( _traits->stencil );
    format.setSampleBuffers( _traits->sampleBuffers );
    format.setSamples( _traits->samples );

    format.setAlpha( _traits->alpha>0 );
    format.setDepth( _traits->depth>0 );
    format.setStencil( _traits->stencil>0 );
    format.setDoubleBuffer( _traits->doubleBuffer );
    format.setSwapInterval( _traits->vsync ? 1 : 0 );
    
    WindowData* windowData = _traits.get() ? dynamic_cast<WindowData*>(_traits->inheritedWindowData.get()) : 0;
    _widget = windowData ? windowData->_widget : 0;
    if ( !_widget )
    {
        GraphicsWindowQt* sharedContextQt = dynamic_cast<GraphicsWindowQt*>(_traits->sharedContext);
        QGLWidget* shareWidget = sharedContextQt ? sharedContextQt->getGraphWidget() : 0;
        
        Qt::WindowFlags flags = Qt::Window|Qt::CustomizeWindowHint;//|Qt::WindowStaysOnTopHint;
        if ( _traits->windowDecoration )
			flags |= Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint|Qt::WindowSystemMenuHint/*|Qt::WindowCloseButtonHint*/;
        
        _widget = new GraphWidget( format, 0, shareWidget, flags );
    }
    
    _widget->setWindowTitle( _traits->windowName.c_str() );
    _widget->move( _traits->x, _traits->y );
    if ( !_traits->supportsResize ) _widget->setFixedSize( _traits->width, _traits->height );
    else _widget->resize( _traits->width, _traits->height );
    
    _widget->setFocusPolicy( Qt::WheelFocus );
    _widget->setGraphicsWindow( this );
    useCursor( _traits->useCursor );

    return true;
}

bool GraphicsWindowQt::setWindowRectangleImplementation( int x, int y, int width, int height )
{
    if ( _widget ) _widget->setGeometry( x, y, width, height );
    return _widget!=NULL;
}

void GraphicsWindowQt::getWindowRectangle( int& x, int& y, int& width, int& height )
{
    if ( _widget )
    {
        const QRect& geom = _widget->geometry();
        x = geom.x();
        y = geom.y();
        width = geom.width();
        height = geom.height();
    }
}

bool GraphicsWindowQt::setWindowDecorationImplementation( bool windowDecoration )
{
    Qt::WindowFlags flags = Qt::Window|Qt::CustomizeWindowHint;//|Qt::WindowStaysOnTopHint;
    if ( windowDecoration )
        flags |= Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint|Qt::WindowSystemMenuHint;
    _traits->windowDecoration = windowDecoration;
    
    // FIXME: Calling setWindowFlags or reparent widget will recreate the window handle,
    // which makes QGLContext no longer work...How to deal with that?
    //if ( _widget ) _widget->setWindowFlags( flags );
    return false;
}

bool GraphicsWindowQt::getWindowDecoration() const
{
    return _traits->windowDecoration;
}

void GraphicsWindowQt::grabFocus()
{
    if ( _widget )
        _widget->setFocus( Qt::ActiveWindowFocusReason );
}

void GraphicsWindowQt::grabFocusIfPointerInWindow()
{
    if ( _widget->underMouse() )
        _widget->setFocus( Qt::ActiveWindowFocusReason );
}

void GraphicsWindowQt::raiseWindow()
{
    if ( _widget )
        _widget->raise();
}

void GraphicsWindowQt::setWindowName( const std::string& name )
{
    if ( _widget )
        _widget->setWindowTitle( name.c_str() );
}

std::string GraphicsWindowQt::getWindowName()
{
    return _widget ? _widget->windowTitle().toStdString() : "";
}

void GraphicsWindowQt::useCursor( bool cursorOn )
{
    if ( _widget )
    {
        _traits->useCursor = cursorOn;
        if ( !cursorOn ) _widget->setCursor( Qt::BlankCursor );
        else _widget->setCursor( _currentCursor );
    }
}

void GraphicsWindowQt::setCursor( MouseCursor cursor )
{
    if ( cursor==InheritCursor && _widget )
    {
        _widget->unsetCursor();
    }

    switch ( cursor )
    {
    case NoCursor: _currentCursor = Qt::BlankCursor; break;
    case RightArrowCursor: case LeftArrowCursor: _currentCursor = Qt::ArrowCursor; break;
    case InfoCursor: _currentCursor = Qt::SizeAllCursor; break;
    case DestroyCursor: _currentCursor = Qt::ForbiddenCursor; break;
    case HelpCursor: _currentCursor = Qt::WhatsThisCursor; break;
    case CycleCursor: _currentCursor = Qt::ForbiddenCursor; break;
    case SprayCursor: _currentCursor = Qt::SizeAllCursor; break;
    case WaitCursor: _currentCursor = Qt::WaitCursor; break;
    case TextCursor: _currentCursor = Qt::IBeamCursor; break;
    case CrosshairCursor: _currentCursor = Qt::CrossCursor; break;
    case HandCursor: _currentCursor = Qt::OpenHandCursor; break;
    case UpDownCursor: _currentCursor = Qt::SizeVerCursor; break;
    case LeftRightCursor: _currentCursor = Qt::SizeHorCursor; break;
    case TopSideCursor: case BottomSideCursor: _currentCursor = Qt::UpArrowCursor; break;
    case LeftSideCursor: case RightSideCursor: _currentCursor = Qt::SizeHorCursor; break;
    case TopLeftCorner: _currentCursor = Qt::SizeBDiagCursor; break;
    case TopRightCorner: _currentCursor = Qt::SizeFDiagCursor; break;
    case BottomRightCorner: _currentCursor = Qt::SizeBDiagCursor; break;
    case BottomLeftCorner: _currentCursor = Qt::SizeFDiagCursor; break;
    default: break;
    };
    if ( _widget ) _widget->setCursor( _currentCursor );
}

bool GraphicsWindowQt::valid() const
{
    return _widget && _widget->isValid();
}

bool GraphicsWindowQt::realizeImplementation()
{
    if ( !_initialized )
        _initialized = init();

    // A makeCurrent()/doneCurrent() seems to be required for
    // realizing the context(?) before starting drawing
    _widget->makeCurrent();
    _widget->doneCurrent();

    _realized = true;
    return true;
}

bool GraphicsWindowQt::isRealizedImplementation() const
{
    return _realized;
}

void GraphicsWindowQt::closeImplementation()
{
    if ( _widget )
        _widget->close();
}

bool GraphicsWindowQt::makeCurrentImplementation()
{
    _widget->makeCurrent();
    return true;
}

bool GraphicsWindowQt::releaseContextImplementation()
{
    _widget->doneCurrent();
    return true;
}

void GraphicsWindowQt::swapBuffersImplementation()
{
    _widget->swapBuffers();
}

void GraphicsWindowQt::requestWarpPointer( float x, float y )
{
    if ( _widget )
        QCursor::setPos( _widget->mapToGlobal(QPoint((int)x,(int)y)) );
}
