#include "animationworld.h"

AnimationWorld::AnimationWorld(int initWidth, int initHeight)
    : width(initWidth), height(initHeight), gravity(0.0f, 0.5f), theWorld(new b2World(gravity))
{
    gatesTimer = new QTimer(this);
    connect(gatesTimer, &QTimer::timeout, this, &AnimationWorld::simulateWorld);
    gatesTimer->start(30);
}

AnimationWorld::AnimationWorld()
{
    // World for confetti
    b2Vec2 gravity(0.0f,  -3.0f);
}

AnimationWorld::~AnimationWorld()
{
    delete theWorld;
}

void AnimationWorld::createBody(float posX, float posY, float boxSize, float density, float friction, float restitution, float angularVelocity, b2Vec2 linearVelocity, float initialAngle)
{
    // Body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(posX, posY);
    bodyDef.angle = initialAngle;
    bodyDef.angularVelocity = angularVelocity;

    // Create a body with the body def
    b2Body* body = theWorld->CreateBody(&bodyDef);

    // Create shape for body
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(boxSize, boxSize);

    // Define fixtures
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    body->CreateFixture(&fixtureDef);
    body->SetLinearVelocity(linearVelocity);

    // Add body to the world
    bodies.push_back(body);

    // Assign a random image
    int randomIndex = QRandomGenerator::global()->bounded(6);
    QVector<QString> gateImages = {
        ":/gatePorts/andGatePorts.png",
        ":/gatePorts/nandGatePorts.png",
        ":/gatePorts/norGatePorts.png",
        ":/gatePorts/notGatePorts.png",
        ":/gatePorts/orGatePorts.png",
        ":/gatePorts/xorGatePorts.png"
    };
    bodyImageMap[body] = gateImages[randomIndex];
}

void AnimationWorld::createRandomBodyAtTop()
{
    float x = randomPosition(this -> width) / SCALE;
    float y = -BODY_MARGIN / SCALE;
    float dynamicBoxSize = 1.0f / SCALE;
    float density = 1.0f;
    float friction = 0.3f;
    float restitution = 0.8f;
    float angularVelocity = 2.0f;
    float linearSpeed = randomSpeed(MIN_SPEED, MAX_SPEED);

    b2Vec2 linearVelocity(0, linearSpeed);
    float initialAngle = QRandomGenerator::global()->bounded(2 * M_PI);
    createBody(x, y, dynamicBoxSize, density, friction, restitution, angularVelocity, linearVelocity, initialAngle);
}

QString AnimationWorld::getImageForBody(b2Body* body) const
{
    return bodyImageMap.value(body, "");
}

void AnimationWorld::resizeWorld(int newWidth, int newHeight)
{
    // Calculate scale ratios of new dimensions to old dimensions
    float widthScale = newWidth / static_cast<float>(this->width);
    float heightScale = newHeight / static_cast<float>(this->height);

    // Update internal dimensions
    this->width = newWidth;
    this->height = newHeight;

    // Adjust positions of bodies proportionally
    for (auto body : bodies)
    {
        b2Vec2 oldPosition = body->GetPosition();
        float newX = oldPosition.x * widthScale;
        float newY = oldPosition.y * heightScale;

        body->SetTransform(b2Vec2(newX, newY), body->GetAngle());
    }
}

QVector<b2Body*> AnimationWorld::getBodies() const
{
    return bodies;
}

b2World *AnimationWorld::getWorld() const
{
    return theWorld;
}


void AnimationWorld::simulateWorld()
{
    theWorld->Step(TIMESTEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

    int randomNumber = QRandomGenerator::global()->bounded(100);
    bool shouldGenerateNewBody = randomNumber < GENERATION_PERCENT;

    // Generate a new shape
    if (shouldGenerateNewBody)
    {
        createRandomBodyAtTop();
    }

    float screenHeight = this->height;

    // Check if any body has hit the "ground"
    for (auto it = bodies.begin(); it != bodies.end();)
    {
        auto& body = *it;
        // Assuming BODY_MARGIN is defined elsewhere
        float bodyBottomPosition = body->GetPosition().y * SCALE - BODY_MARGIN;

        // If the bottom of the body is below the screenHeight
        if (bodyBottomPosition > screenHeight)
        {
            // Destroy the body from the world
            theWorld->DestroyBody(body);

            // Remove the body from the bodies vector
            it = bodies.erase(it);
        }
        else
        {
            // Move to the next element
            ++it;
        }
    }
    updateCursorPosition(QCursor::pos());
}

void AnimationWorld::updateCursorPosition(QPoint cursorPosition)
{
    // Get the current mouse position
    cursorPosition = QCursor::pos();

    // Calculate the direction based on the mouse position
    float direction = 0.0f;
    if (cursorPosition.x() < this->width / 2) {
        direction = -1.0f; // Move left
    } else {
        direction = 1.0f; // Move right
    }

    // Update the direction of the existing shapes
    for (auto body : bodies) {
        b2Vec2 linearVelocity = body->GetLinearVelocity();
        linearVelocity.x = (direction) * std::abs(linearVelocity.x);
        body->SetLinearVelocity(linearVelocity);
        body->SetAngularVelocity(direction * 4.0f);
    }}

float AnimationWorld::randomPosition(int max)
{
    return static_cast<float>(QRandomGenerator::global()->bounded(max));
}

float AnimationWorld::randomSpeed(float minSpeed, float maxSpeed)
{
    auto& rand = *QRandomGenerator::global();
    double normalizedRandom = rand.generateDouble();
    float range = maxSpeed - minSpeed;
    float speed = minSpeed + static_cast<float>(normalizedRandom * range);

    return speed;
}
