#include "GlobalCurveState.h"

#include <QMutex>


GlobalCurveState *GlobalCurveState::m_GlobalCurveState = nullptr;

GlobalCurveState *GlobalCurveState::getInstance()
{
    QMutex mutex;
    if(m_GlobalCurveState == nullptr)
    {
        QMutexLocker locker(&mutex);
        m_GlobalCurveState = new GlobalCurveState();
        locker.unlock();
    }
    return m_GlobalCurveState;
}

void GlobalCurveState::releaseGlobalCurveState()
{
    IsGlobal = false;
    m_WheelEvent = nullptr;
    m_MousePressEvent = nullptr;
    m_MouseReleaseEvent = nullptr;
    m_MouseMoveEvent = nullptr;
}

GlobalCurveState::GlobalCurveState(QObject *parent) : QObject(parent)
{

}

GlobalCurveState::~GlobalCurveState()
{
    if(m_GlobalCurveState)
    {
        delete m_GlobalCurveState;
        m_GlobalCurveState = nullptr;
    }
}

QPoint GlobalCurveState::getGlobalPos()
{
    return curvePos;
}

void GlobalCurveState::setGlobalPos(QPoint pos)
{
    curvePos = pos;
}

bool GlobalCurveState::getGlobalState()
{
    return IsGlobal;
}

void GlobalCurveState::setGlobalState(bool isTrue)
{
    IsGlobal = isTrue;
}

void GlobalCurveState::setGlobalWheelEvent(QWheelEvent *event)
{
    m_WheelEvent = event;
}

QWheelEvent *GlobalCurveState::getGlobalWheelEvent()
{
    return m_WheelEvent;
}

void GlobalCurveState::setGlobalMousePress(QMouseEvent *event)
{
    m_MousePressEvent = event;
}

QMouseEvent *GlobalCurveState::getGlobalMousePress()
{
    return m_MousePressEvent;
}

void GlobalCurveState::setGlobalMouseRelease(QMouseEvent *event)
{
    m_MouseReleaseEvent = event;
}

QMouseEvent *GlobalCurveState::getGlobalMouseRelease()
{
    return m_MouseReleaseEvent;
}

void GlobalCurveState::setGlobalMouseMove(QMouseEvent *event)
{
    m_MouseMoveEvent = event;
}

QMouseEvent *GlobalCurveState::getGlobalMouseMove()
{
    return m_MouseMoveEvent;
}

void GlobalCurveState::setGlobalActiveWindowId(QString id)
{
    m_GlobalActiveWindowId = id;
}

QString GlobalCurveState::getGlobalActiveWindowId()
{
    return m_GlobalActiveWindowId;
}

void GlobalCurveState::setGlobalWindows(bool isTrue)
{
    IsGlobalWindows = isTrue;
}

bool GlobalCurveState::getGlobalWindows()
{
    return IsGlobalWindows;
}
