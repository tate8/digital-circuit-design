#ifndef ANIMATIONWORLD_H
#define ANIMATIONWORLD_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jasmine Robbins

#include <QColor>
#include <QObject>
#include <Box2D/Box2D.h>
#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include <QMap>

/// @brief This class manages the physics-based animation of objects
/// in a simulated 2D world using the Box2D library.
class AnimationWorld : public QObject
{
    Q_OBJECT

public:
    static constexpr float TIMESTEP = 1.0f / 150.0f;
    static constexpr int VELOCITY_ITERATIONS = 8;
    static constexpr int POSITION_ITERATIONS = 3;
    static constexpr float BODY_MARGIN = 50.0f;
    static constexpr float MIN_SPEED = 6.0f;
    static constexpr float MAX_SPEED = 10.0f;
    static constexpr float GENERATION_PERCENT = 5;

    /// @brief The Scale factor is used to convert between pixels and Box2D world
    /// coordinates. Pixels are converted to world coordinates by dividing by SCALE.
    /// The World coordinates are converted to pixel coordinates by multiplying by SCALE.
    const float SCALE = 50.0f;

    /// @brief Constructor to initialize the Box2D world for background animation.
    /// @param initWidth - the initial width of the ui window
    /// @param initHeight - the initial height of the ui window
    AnimationWorld(int initWidth, int initHeight);

    /// @brief Default Constructor for creating confetti animation.
    AnimationWorld();

    /// @brief Destructor to clean up resources.
    ~AnimationWorld();

    /// @brief Simulates the physics world and handles updating the bodies for background
    ///  animation.
    void simulateWorld();

    /// @brief Resizes the Box2D world when the ui window is resized.
    /// @param newWidth - width of the screen
    /// @param newHeight - height of the screen
    void resizeWorld(int newWidth, int newHeight);

    /// @brief Retrieves all bodies in the world.
    /// @return a vector containing pointers to all bodies
    QVector<b2Body*>getBodies() const;

    /// @brief Gets the animation world.
    /// @return Pointer to the world
    b2World *getWorld() const;

    /// @brief Gets the confetti bodies as a pair. The body contains the information
    /// for the confetti, and each piece is generated with a color.
    QVector<QPair<b2Body*, QColor>> getConfettiBodies() const;

    /// @brief Gets the image resource string corresponding to a body
    /// @param body - The body whose image to get
    QString getImageForBody(b2Body* body) const;

public slots:
    /// @brief Creates confetti at x,y coords. based on the ui screen size.
    void createConfetti(float x, float y);

    /// @brief Starts the simulation for a given amount of time.
    void startConfetti();

    /// @brief Steps through the confetti world to simulate the animation.
    void updateConfetti();

signals:
    /// @brief Signal to send back to the view for the animation to be updated.
    void confettiUpdated();

private:
    /// @brief the width of the Box2D world.
    int width;

    /// @brief the height of the Box2D world.
    int height;

    /// @brief The gravitational force applied in the world.
    b2Vec2 gravity;

    /// @brief Defines the Box2D world that holds the bodies and simulation.
    b2World *theWorld;

    /// @brief Defines the Box2D world for the confetti simulation when the user
    /// completes a circuit correclty.
    b2World *confettiWorld;

    /// @brief List of all bodies created for background animation.
    QVector<b2Body*> bodies{};

    /// @brief Creates a new physics body in the world.
    /// @param posX - x-coordinate in pixels
    /// @param posY - y-coordinate in pixels
    /// @param boxSize - size of the body's box shape, in pixels
    /// @param density - mass of the body
    /// @param friction - surface friction
    /// @param restitution - body's bounciness
    /// @param angularVelocity - initial angular velocity in radians per second
    /// @param linearVelocity - initial linear velocity in pixels per second
    /// @param initialAngle - initial angle
    void createBody(float posX, float posY, float boxSize, float density, float friction, float restitution, float angularVelocity, b2Vec2 linearVelocity, float initialAngle);

    /// @brief Creates a random body at the top of the screen
    void createRandomBodyAtTop();

    /// @brief Generates a random coordinate value
    /// @param max - the upper limit of the random value
    /// @return the randomly generated coordinate
    float randomPosition(int max);

    /// @brief Generates a random speed within a specified range.
    /// @param minSpeed: minumum speed
    /// @param maxSpeed: maximum speed
    /// @return a random speed for the world simulation
    float randomSpeed(float minSpeed, float maxSpeed);

    /// @brief Stores the colors for the confetti.
    QVector<QColor> confettiColors =
    {
        QColor(247, 91, 171),   // pink
        QColor(4, 202, 246),    // blue
        QColor(204, 170, 255),  // purple
        QColor(255, 180, 93),   // orange
        QColor(255, 255, 0),    // yellow
        QColor(16, 253, 28)     // green
    };

    /// @brief Stores the confetti bodies with their body definitions and color.
    QVector<QPair<b2Body*, QColor>> confettiBodies{};

    /// @brief Timer for confetti animation
    QTimer* confettiTimer = nullptr;

    /// @brief Timer for gates animation
    QTimer* gatesTimer = nullptr;

    /// @brief Map from body to its image resource string
    QMap<b2Body*, QString> bodyImageMap;
};

#endif // ANIMATIONWORLD_H
