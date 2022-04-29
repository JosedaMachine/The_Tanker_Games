#include "AsteroidsSystem.h"
#include "GameCtrlSystem.h"

#include "../components/AsteroidType.h"
#include "../components/FrameImage.h"
#include "../components/Generations.h"

AsteroidsSystem::AsteroidsSystem(const int numAsteroids_, const int t_, const float w, const float h) :
	numAsteroids(numAsteroids_), timer(t_), widthAst_(w), heightAst_(h)
{
	generations_ = 0;
}


AsteroidsSystem::~AsteroidsSystem()
{
}

void AsteroidsSystem::init() {
	lastTime = sdlutils().currRealTime();
}

void AsteroidsSystem::update() {
	//Comprobamos el estado del juego
	GameCtrlSystem* gSys = manager_->getSystem<GameCtrlSystem>();
	if (gSys->getGameState() == GameState::RUNNING) {

		playerPos = &(manager_->getComponent<Transform>(manager_->getHandler<Player>())->pos_);

		for (Entity* asteroid : manager_->getEnteties()) {
			if (manager_->hasGroup<Asteroid_grp>(asteroid)) {
				auto* tr = manager_->getComponent<Transform>(asteroid);

				tr->pos_ = tr->pos_ + tr->vel_;

				auto* opposieSide = manager_->getComponent<ShowAtOpposieSide>(asteroid);


				Vector2D pos = tr->pos_;
				//Guardamos las posici�n
				float x = pos.getX();
				float y = pos.getY();

				if (x > opposieSide->windowW)
					//Le restamos su anchura porque si no aparece autom�ticamente en pantalla	
					tr->pos_.setX(0 - opposieSide->w);
				else if (x < 0 - opposieSide->w) 	//Le restamos su anchura porque si no se trigerea en cuanto toca el borde
					tr->pos_.setX(opposieSide->windowW);
				else if (y < 0 - opposieSide->h)//Le restamos su altura porque si no aparece autom�ticamente en pantalla	
					tr->pos_.setY(opposieSide->windowH);
				else if (y > opposieSide->windowH + opposieSide->h)//Le sumamos su altura sporque si no se trigerea en cuanto toca el borde
					tr->pos_.setY(0 - opposieSide->h);

				auto* type = manager_->getComponent<AsteroidType>(asteroid);

				if (type != nullptr) {
					if (type->type_ == AsteroidType::Type::B) {
						auto& vel = tr->vel_;
						Vector2D p = tr->pos_;
						vel.set(vel.rotate(vel.angle(*playerPos - p) > 0 ? 1.0f : -1.0f));
					}
				}
			}
		}
		//Timer de creación de los asteroides
		if (sdlutils().currRealTime() - lastTime >= timer && generations_ > 0) {
			lastTime = sdlutils().currRealTime();
			addAsteroids();
		}
		//Comprobación de ganar el juego
		if (generations_ <= 0) {
			gSys->setWin(true);
			gSys->setState(GameState::GAMEOVER);
		}
	}
}

void  AsteroidsSystem::startGame() {
	for (int i = 0; i < numAsteroids; i++) addAsteroids();
}

/// <summary>
/// Divide un asteroide si es posible, en dos más pequeños
/// </summary>
/// <param name="golden">es de tipo B</param>
/// <param name="numGenerations">generaciones restantes del padre</param>
/// <param name="ast">asteroide padre</param>
void AsteroidsSystem::divide(bool golden, const int& numGenerations, Entity* ast)
{
	generations_++;
	Transform* t = manager_->getComponent<Transform>(ast);
	Vector2D p = t->pos_;
	Vector2D v = t->vel_;
	float width = t->width_;

	int r = sdlutils().rand().nextInt(0, 360);
	Vector2D astPos = p + v.rotate(r) * 2 * width;
	Vector2D astVel = v.rotate(r) * 1.1f;

	auto* asteroid = manager_->addEntity();
	manager_->addComponent<Transform>(asteroid, astPos, astVel, widthAst_ + 5.0f * numGenerations, heightAst_ + 5 * numGenerations, 0.0f);

	if (!golden) manager_->addComponent<FrameImage>(asteroid, &sdlutils().images().at("asteroidA"), 5, 6, 0, 0, 50.0f);
	else manager_->addComponent<FrameImage>(asteroid, &sdlutils().images().at("asteroidB"), 5, 6, 0, 0, 50.0f);

	manager_->addComponent<ShowAtOpposieSide>(asteroid, asteroid, manager_, Vector2D((float)sdlutils().width(), (float)sdlutils().height()));
	manager_->addComponent<Generations>(asteroid, numGenerations);

	//Si es de tipo B, hacemos que siga al jugador
	if (golden) manager_->addComponent<AsteroidType>(asteroid, AsteroidType::Type::B);
	//Asignamos su grupo
	manager_->setGroup<Asteroid_grp>(asteroid, true);
}

void AsteroidsSystem::addAsteroids(int nGenerations) {
	generations_++;
	bool isA = (sdlutils().rand().nextInt(0, 10) < 3 ? true : false);
	auto* asteroid = manager_->addEntity();
	//Random para saber en qu� eje hacer el random de la posicion en los bordes
	int posibility = sdlutils().rand().nextInt(0, 2);
	//Centro de la pantalla
	Vector2D center = Vector2D((float)sdlutils().width() / 2.0f, (float)sdlutils().height() / 2.0f);
	//Posicion central de la pantalla aleatoria
	Vector2D finalPos = Vector2D(center.getX() + sdlutils().rand().nextInt(-100, 100), center.getY() + sdlutils().rand().nextInt(-100, 100));
	Vector2D pos;
	int posRandom;
	//Random en eje X
	if (posibility == 0) {
		posibility = sdlutils().rand().nextInt(0, 2);
		posRandom = sdlutils().rand().nextInt(0, (sdlutils().width() + 1));
		pos.setX((float)posRandom);
		if (posibility == 0) pos.setX(0);
		else pos.setX((float)sdlutils().height());
	}
	else { //Random en eje X
		posibility = sdlutils().rand().nextInt(0, 2);
		posRandom = sdlutils().rand().nextInt(0, (sdlutils().height() + 1));
		pos.setY((float)posRandom);
		if (posibility == 0) pos.setX(0);
		else pos.setX((float)sdlutils().width());
	}
	//Hacemos que vaya a la position aleatoria del centro
	Vector2D v = Vector2D(finalPos - pos).normalize() * (sdlutils().rand().nextInt(1, 10) / 9.0f);
	manager_->addComponent<Transform>(asteroid, pos, v, widthAst_ + 5.0f * nGenerations, heightAst_ + 5 * nGenerations, 0.0f);

	//Diferenciamos entre tipo A o B
	if (!isA) {
		manager_->addComponent<AsteroidType>(asteroid, AsteroidType::Type::A);
		manager_->addComponent<FrameImage>(asteroid, &sdlutils().images().at("asteroidA"), 5, 6, 0, 0, 50.0f);
	}
	else {
		manager_->addComponent<AsteroidType>(asteroid, AsteroidType::Type::B);
		manager_->addComponent<FrameImage>(asteroid, &sdlutils().images().at("asteroidB"), 5, 6, 0, 0, 50.0f);
	}


	manager_->addComponent<ShowAtOpposieSide>(asteroid, asteroid, manager_, Vector2D((float)sdlutils().width(), (float)sdlutils().height()));
	manager_->addComponent<Generations>(asteroid, nGenerations);
	//Asignamos su grupo
	manager_->setGroup<Asteroid_grp>(asteroid, true);
}

void AsteroidsSystem::onCollisionWithBullet(Entity* asteroid, Entity* b) {
	//Desactivas asteroide

	if (manager_->isActive(asteroid)) {
		manager_->setActive(asteroid, false);
		generations_--;
	}
	//Componente generatios, se le resta y se comprueba si tiene
	Generations* n = manager_->getComponent<Generations>(asteroid);
	//Generations* n = asteroid->getComponent<Generations>();
	n->generations_--;

	if (n->generations_ > 0) {
		for (int i = 0; i < 2; i++) {
			AsteroidType* type = manager_->getComponent<AsteroidType>(asteroid);
			if (type != nullptr) {
				divide(type->type_ == AsteroidType::Type::B, n->generations_, asteroid);
			}
		}
	}
}

int AsteroidsSystem::getGenerations() {
	return generations_;
}
