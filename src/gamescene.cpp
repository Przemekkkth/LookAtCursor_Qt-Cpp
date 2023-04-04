#include "gamescene.h"
#include "utils.h"
#include "pixmapmanager.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QDir>
#include <QPainter>
#include "circle.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    onUserCreate();
    setBackgroundBrush(Qt::black);
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i] = new KeyStatus();
    }
    m_mouse = new MouseStatus();
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    while(m_loopTime > m_loopSpeed)
    {
        m_loopTime -= m_loopSpeed;
        handlePlayerInput();
        clear();

        for (auto& unit : vecUnits)
        {

            float fAngleToNewTarget = atan2(unit.vPosition.y() - vTarget.y(), unit.vPosition.x() - vTarget.x()) + 3.14159f;

            float delta = circ_shortdiff(unit.fHeading, fAngleToNewTarget, 0.0f, 2.0f * 3.14159f);
            unit.fHeading = circ_add(unit.fHeading, delta * 0.1f * 10.0f, 0.0f, 2.0f * 3.14159f);

            QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
            pItem->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Eye));
            pItem->setPos(unit.vPosition.x(), unit.vPosition.y());
            //half of eye pixmap 15x16
            pItem->setTransformOriginPoint(15, 16);
            pItem->setRotation(unit.fHeading * (180.0f/3.14f));
            addItem(pItem);
        }
        drawHero();

        resetStatus();
    }
}

void GameScene::onUserCreate()
{
    int nUnits = 60;
    for (int i = 0; i < nUnits; i++)
    {
        vecUnits.push_back(
                    //angle, pos, target
                    { 0.0f, QVector2D(rand()%SCREEN::PHYSICAL_SIZE.width(), rand() %SCREEN::PHYSICAL_SIZE.height()), QVector2D(0.0f, 0.0f)});


    }
}

void GameScene::drawHero()
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Hero));
    //half of hero(16px) pixmap
    pItem->setPos(vTarget.x()-16.0f, vTarget.y()-16.0f);
    addItem(pItem);
}

void GameScene::handlePlayerInput()
{
    if(m_mouse->m_pressed)
    {
        vTarget = QVector2D(m_mouse->m_x, m_mouse->m_y);
    }
}

void GameScene::resetStatus()
{
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i]->m_released = false;
    }
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i]->m_pressed = false;
    }
    m_mouse->m_released = false;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(KEYBOARD::KeysMapper.contains(event->key()))
    {
        if(event->isAutoRepeat())
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held = true;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = false;
        }
        else
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = true;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held    = false;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(KEYBOARD::KeysMapper.contains(event->key()))
    {
        if(!event->isAutoRepeat())
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held = false;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = false;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_released = true;
        }

    }
    QGraphicsScene::keyReleaseEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = true;
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    QGraphicsScene::mouseMoveEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = false;
    m_mouse->m_released = true;
    QGraphicsScene::mouseReleaseEvent(event);
}
