#include "animationworld.h"

AnimationWorld::AnimationWorld(int initWidth, int initHeight)
    : width(initWidth), height(initHeight), gravity(0.0f, 0.5f), theWorld(new b2World(gravity))
{
    // Bodies for background animation
    initializeBodies(20);
}

AnimationWorld::AnimationWorld()
{
    // World for confetti
    b2Vec2 gravity(0.0f,  -3.0f);
    confettiWorld = new b2World(gravity);
}

AnimationWorld::~AnimationWorld()
{
    delete confettiWorld;
    delete theWorld;
}

void AnimationWorld::initializeBodies(int numBodies)
{
    for (int i = 0; i < numBodies; i++)
    {
        // Pixel coords converted to box2D coords.
        float x = randomPosition(this -> width) / SCALE;
        float y = randomPosition(this -> height) / SCALE;
        float dynamicBoxSize = 1.0f / SCALE;
        float density = 1.0f;
        float friction = 0.3f;
        float restitution = 0.8f;
        float angularVelocity = 2.0f;
        float linearSpeed = randomSpeed(1.0f, 3.0f);
        b2Vec2 linearVelocity(0, linearSpeed);
        float initialAngle = QRandomGenerator::global()->bounded(2 * M_PI);
        createBody(x, y, dynamicBoxSize, density, friction, restitution, angularVelocity, linearVelocity, initialAngle);
    }
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

QString AnimationWorld::getImageForBody(b2Body* body) const
{
    return bodyImageMap.value(body, "");
}

void AnimationWorld::resetBody(b2Body *body)
{
    float x = randomPosition(this->width) / SCALE;
    float y = -BODY_MARGIN / SCALE;  // Reset to top
    body->SetTransform(b2Vec2(x, y), 0);
    float linearSpeed = randomSpeed(1.0f, 3.0f);
    b2Vec2 linearVelocity(0, linearSpeed);
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
    float screenHeight = this->height;

    // Check if any body has hit the "ground"
    for (auto& body : bodies)
    {
        if (body->GetPosition().y * SCALE  - BODY_MARGIN > screenHeight)
        {
            resetBody(body);
        }
    }
}

QVector<QPair<b2Body*, QColor>> AnimationWorld::getConfettiBodies() const
{
    return confettiBodies;
}


void AnimationWorld::createConfetti(float x, float y)
{
    // if (confettiTimer && confettiTimer->isActive())
    // {
    //     confettiTimer->stop();
    // } else
    // {
    //     confettiTimer = new QTimer(this);
    // }
    for (auto& pair : confettiBodies)
    {
        confettiWorld->DestroyBody(pair.first);
    }
    confettiBodies.clear();


    float centerX = x / SCALE;
    float centerY = y / SCALE;
    float spread = 0.4f;

    for (int i = 0; i < 300; ++i)
    {
        float angle = QRandomGenerator::global()->generate() / static_cast<double>(UINT_MAX) * 2 * M_PI;
        float randomMinSpeed = 3.0f + static_cast<float>(QRandomGenerator::global()->bounded(2));
        float randomMaxSpeed = 10.0f + static_cast<float>(QRandomGenerator::global()->bounded(5));
        float speed = randomSpeed(randomMinSpeed, randomMaxSpeed);
        float angularVelocity = 0.2f;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.linearDamping = 0.5;
        bodyDef.angularVelocity = angularVelocity;
        bodyDef.position.Set(centerX + spread * cos(angle), centerY + spread * sin(angle));

        b2Body* body = confettiWorld->CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1.0f / SCALE, 1.0f / SCALE);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 0.1f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.8f;
        body->CreateFixture(&fixtureDef);
        body->SetLinearVelocity(b2Vec2(speed * cos(angle), speed * sin(angle)));

        // Select a random color from the confettiColors list and store body as a pair
        QColor color = confettiColors[rand() % confettiColors.size()];
        confettiBodies.push_back(qMakePair(body, color));
    }
}

void AnimationWorld::updateConfetti()
{
    const float timeStep = 1.0f / 80.0f;
    const int velocityIterations = 8;
    const int positionIterations = 3;
    confettiWorld->Step(timeStep, velocityIterations, positionIterations);

    emit confettiUpdated();
}

void AnimationWorld::startConfetti()
{
    // simulate confetti
    confettiTimer = new QTimer(this);
    connect(confettiTimer, &QTimer::timeout, this, &AnimationWorld::updateConfetti);
    confettiTimer->start(20);
}

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
