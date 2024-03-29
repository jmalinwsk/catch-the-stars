#include <vector>

class Model;
bool checkIfNoCollisions(glm::vec3 position);
void checkForStarsToCollect(glm::vec3 position);
class ConfettiModel;
class Program;
class Font;
class Text;
class Ground;

std::vector<Model> models;
std::vector<Text> texts;
ConfettiModel* confettiModel;
Ground* ground;

glm::mat4 matProj;
glm::mat4 matView;
glm::mat4 matModel;
glm::mat4 matProjView;
glm::mat3 matNormal;

int frameCounter;
int starCounter;
int countdownTimerCounter = 20;

const char* skyboxFiles[6] = {
	"textures/skybox/posx.png",
	"textures/skybox/negx.png",
	"textures/skybox/posy.png",
	"textures/skybox/negy.png",
	"textures/skybox/posz.png",
	"textures/skybox/negz.png"
};

bool keyboardActive = true;