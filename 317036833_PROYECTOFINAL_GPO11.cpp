#include <iostream>
#include <cmath>
#include <math.h>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "modelAnim.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animacionMariposa();
void animCapibara();
void keyframeLion();
void animCocodrilo();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(-100.0f, 2.0f, -45.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
float movCamera = 0.0f;
int raiz = 1;
//Animation Capybara
float rotKit = -90.0f;
float rotKitZ = 0.0f;
float movXCapibara = 13.5f,movZCapibara = 1.5f, movYCapibara = 0.5f;
float pataTrasera = 0.0f, pataDelantera = 0.0f;
bool recorrido1 = true, recorrido2 = false, recorrido3 = false, recorrido4 = false, 
recorrido5 = false, recorrido6 = false, recorrido7 = false, recorrido8 = false,
animPatasDel = false, animPatasTras = false, recorridoCapibara = false;

//Animation butterfly
float rot1 = 0.0f;
float rot2 = 0.0f;
float movKitX = 0.0f;
float movKitZ = 1.0f;
float rotMariposa = -90.0;
bool recorridoMariposa = false, anim = false, anim2 = false, direccion = true;

//Animation crocodile
float rotYCoco = 0.0f,rotPatasCo = 0.0f, rotColaCo = 0.0f, movYCoco = 0.0f, movCoco = 0.0f;
bool recorridoCoco = false, rotPatas1 = false, rotPatas2 = false, rotCola1 = false, rotCola2 = false;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

bool active;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


float posXCa = PosIni.x + 84.22f, posYCa = PosIni.y, posZCa = PosIni.z + 44.191f;
float posXMari = PosIni.x, posYMari = PosIni.y, posZMari = PosIni.z + 44.768f;

float posXLeones = PosIni.x - 13.277, posYLeones = PosIni.y - 3.134, posZLeones = PosIni.z - 44.467;
float posXPanda = PosIni.x + 86.652f, posYPanda = PosIni.y, posZPanda = PosIni.z - 43.570;
float posXPenguin = PosIni.x, posYPenguin = PosIni.y - 5.535, posZPenguin = PosIni.z;
float posXHerp = PosIni.x + 74.816, posYHerp = PosIni.y, posZHerp = PosIni.z;
float posXEnvi = PosIni.x, posYEnvi = PosIni.y, posZEnvi = PosIni.z;

// Keyframes
float rotBicepDer = 0.0f, rotBicepIzq = 0.0f, rotAnteDer = 0.0f, rotAnteIzq = 0.0f, rotManoDer = 0.0f,
rotManoIzq = 0.0f, rotCabeza = 0.0f, posX = posXLeones, posY = posYLeones, posZ = posZLeones;

#define MAX_FRAMES 4
int i_max_steps = 50;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotBicepDer, rotBicepIzq, rotAnteDer, rotAnteIzq, rotManoDer,
	rotManoIzq, rotCabeza;
	float rotIncBicepDer, rotIncBicepIzq, rotIncAnteDer, rotIncAnteIzq, rotIncManoDer,
	rotIncManoIzq, rotIncCabeza;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 4;			//introducir datos
bool play = false;
int playIndex = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	//glm::vec3(posX-4.8,posY+4,posZ+0.65),
	//glm::vec3(posX+4.8,posY+4,posZ+0.65),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0)
};

glm::vec3 LightP1;

float frameX[MAX_FRAMES] = { -108.277,-108.277,-108.277,-108.277};
float frameY[MAX_FRAMES] = { -2.134,-2.134,-2.134,-2.134};
float frameZ[MAX_FRAMES] = {-89.467,-89.467 ,-89.467 ,-89.467 };

float rBicepDer[MAX_FRAMES] = { -3,-56,-56,-56};
float rAntebrazoDer[MAX_FRAMES] = {0,0,-32,-32};
float rManoDer[MAX_FRAMES] = {0,0,0,-81};

float rBicepIzq[MAX_FRAMES] = { 0,-73,-82,-82};
float rAntebrazoIzq[MAX_FRAMES] = {0,0,-50,-50};
float rManoIzq[MAX_FRAMES] = { 0,0,0,90};

float rCabeza[MAX_FRAMES] = {0,0,0,79};

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotBicepDer = KeyFrame[0].rotBicepDer;
	rotAnteDer = KeyFrame[0].rotAnteDer;
	rotManoDer = KeyFrame[0].rotManoDer;
	rotBicepIzq = KeyFrame[0].rotBicepIzq;
	rotAnteIzq = KeyFrame[0].rotAnteIzq;
	rotManoIzq = KeyFrame[0].rotManoIzq;
	rotCabeza = KeyFrame[0].rotCabeza;
}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	
	KeyFrame[playIndex].rotIncBicepDer = (KeyFrame[playIndex + 1].rotBicepDer - KeyFrame[playIndex].rotBicepDer) / i_max_steps;
	KeyFrame[playIndex].rotIncAnteDer = (KeyFrame[playIndex + 1].rotAnteDer - KeyFrame[playIndex].rotAnteDer) / i_max_steps;
	KeyFrame[playIndex].rotIncManoDer = (KeyFrame[playIndex + 1].rotManoDer - KeyFrame[playIndex].rotManoDer) / i_max_steps;

	KeyFrame[playIndex].rotIncBicepIzq = (KeyFrame[playIndex + 1].rotBicepIzq - KeyFrame[playIndex].rotBicepIzq) / i_max_steps;
	KeyFrame[playIndex].rotIncAnteIzq = (KeyFrame[playIndex + 1].rotAnteIzq - KeyFrame[playIndex].rotAnteIzq) / i_max_steps;
	KeyFrame[playIndex].rotIncManoIzq = (KeyFrame[playIndex + 1].rotManoIzq - KeyFrame[playIndex].rotManoIzq) / i_max_steps;
	
	KeyFrame[playIndex].rotIncCabeza = (KeyFrame[playIndex + 1].rotCabeza - KeyFrame[playIndex].rotCabeza) / i_max_steps;
}




int main()
{
	// Init GLFW
	glfwInit();




	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.frag");

	////Carga de modelos del mariposario
	//Model domo((char*)"Models/Mariposario/Domo/Domo.obj");
	//Model cristales((char*)"Models/Mariposario/Domo/CristalesDomo.obj");
	//Model estructura((char*)"Models/Mariposario/Street_lamp/estructura.obj");
	//Model foco((char*)"Models/Mariposario/Street_lamp/foco.obj");
	//Model banca((char*)"Models/Mariposario/Bank/Bank.obj");
	//Model arbol((char*)"Models/Mariposario/tree/tree.obj");
	//Model cuerpoMari((char*)"Models/Mariposario/Butterfly/body.obj");
	//Model alaIzq((char*)"Models/Mariposario/Butterfly/wing_left.obj");
	//Model alaDer((char*)"Models/Mariposario/Butterfly/wing_right.obj");

	////Carga de modelos de capibaras
	//Model casaCapi((char*)"Models/Capibaras/caseta/CasaDescanso.obj");
	//Model cristalCasa((char*)"Models/Capibaras/caseta/Cristal.obj");
	//Model barda((char*)"Models/Capibaras/habitat/Barda.obj");
	//Model cristalesBarda((char*)"Models/Capibaras/habitat/Cristales.obj");
	//Model planta((char*)"Models/Capibaras/habitat/plantas.obj");
	//Model rocas((char*)"Models/Capibaras/RocasAmbiente/rocas.obj");
	//Model tina((char*)"Models/Capibaras/tina/Tina.obj");
	//Model aguaTina((char*)"Models/Capibaras/tina/Agua.obj");
	//
	////Capybara 
	//Model piernaDelanDer((char*)"Models/Capibaras/capibara/piernaDD.obj");
	//Model piernaDelanIzq((char*)"Models/Capibaras/capibara/piernaDI.obj");
	//Model piernaTraseDer((char*)"Models/Capibaras/capibara/piernaTD.obj");
	//Model piernaTraseIzq((char*)"Models/Capibaras/capibara/piernaTI.obj");
	//Model capibara((char*)"Models/Capibaras/capibara/cuerpo.obj");


	//Lion's habitat model declarations
	Model lionFloor((char*)"Models/HabitatLeones/FloorModel/FloorPlane.obj");
	Model lionRocks((char*)"Models/HabitatLeones/RockCollection/Rocks.obj");
	Model lionWater((char*)"Models/HabitatLeones/WaterLakeModel/WaterPlane.obj");
	Model lionATree((char*)"Models/HabitatLeones/Tree/ATree.obj");
	Model lionBTree((char*)"Models/HabitatLeones/Tree/BTree.obj");
	Model lionCTree((char*)"Models/HabitatLeones/Tree/CTree.obj");
	Model lionFences((char*)"Models/HabitatLeones/FencesModel/FenceModel.obj");
	Model lionExterior((char*)"Models/HabitatLeones/ConcreteExterior/BaseExterior.obj");
	Model scar((char*)"Models/HabitatLeones/personajes/scar/scar.obj");
	Model simba((char*)"Models/HabitatLeones/personajes/simba/simba.obj");

	//Lion animate
	Model bodyLion((char*)"Models/HabitatLeones/personajes/alexLion/cuerpo.obj");
	Model headLion((char*)"Models/HabitatLeones/personajes/alexLion/cabeza.obj");
	Model bicepDer((char*)"Models/HabitatLeones/personajes/alexLion/bicepDer.obj");
	Model bicepIzq((char*)"Models/HabitatLeones/personajes/alexLion/bicepIzq.obj");
	Model antebrazoDer((char*)"Models/HabitatLeones/personajes/alexLion/antebrazoDer.obj");
	Model antebrazoIzq((char*)"Models/HabitatLeones/personajes/alexLion/antebrazoIzq.obj");
	Model manoDer((char*)"Models/HabitatLeones/personajes/alexLion/manoDer.obj");
	Model manoIzq((char*)"Models/HabitatLeones/personajes/alexLion/manoIzq.obj");

	////Panda's habitat model declaration
	//Model pandaFloor((char*)"Models/HabitatPanda/GrassPlane/GrassPlane.obj");
	//Model pandaRocks((char*)"Models/HabitatPanda/Rocks/Rock.obj");
	//Model pandaFence((char*)"Models/HabitatPanda/FenceModel/FenceModel.obj");
	//Model pandaChineseBuilding((char*)"Models/HabitatPanda/ChineseBuilding/ChineseBuilding.obj");
	//Model pandaBambuPlant((char*)"Models/HabitatPanda/BambuPlant/BambuPlant.obj");
	//Model pandaWaterWell((char*)"Models/HabitatPanda/WaterWallModel/WaterWell.obj");

	////Penguin's habitat model declaration
	//Model penguinCenter((char*)"Models/HabitatPinguinos/CentralBaseModel/Center.obj");
	//Model penguinExternal((char*)"Models/HabitatPinguinos/ExternalBaseModel/ExternalBaseModel.obj");
	//Model penguinFloor((char*)"Models/HabitatPinguinos/FloorModel/Floor.obj");
	//Model penguinBowl((char*)"Models/HabitatPinguinos/PenguinBowlModel/Bowl.obj");
	//Model penguinRailing((char*)"Models/HabitatPinguinos/RailingModel/RailingModel.obj");
	//Model penguinStreet((char*)"Models/HabitatPinguinos/StreetLampModel/StreetLamp.obj");
	//Model penguinStreetGlass((char*)"Models/HabitatPinguinos/StreetLampModel/StreetLampGlass.obj");
	//Model penguinWater((char*)"Models/HabitatPinguinos/WaterPlane/Water.obj");

	////Enviroment models 
	//Model enviGrassPlane((char*)"Models/Entorno/GrassPlane/GrassPlane.obj");
	//Model enviContorno((char*)"Models/Entorno/ConcreteLimit/Contorno.obj");
	//Model enviGate((char*)"Models/Entorno/Gate/wooden_gate.obj");
	//Model enviRoad((char*)"Models/Entorno/Road/Road.obj");
	//Model enviFrontFence((char*)"Models/Entorno/Fence/FrontFence.obj");
	//Model enviBackFence((char*)"Models/Entorno/Fence/BackFence.obj");
	//Model enviLateralFence((char*)"Models/Entorno/Fence/LateralFence.obj");
	//Model enviHerpFloor((char*)"Models/Herpetario/Floor/Floor.obj");
	//Model enviStreetLight((char*)"Models/Entorno/StreetLight/StreetLight.obj");
	//Model enviStreetLightGlass((char*)"Models/Entorno/StreetLight/StreetLightGlass.obj");
	//Model enviTree((char*)"Models/Entorno/tree/tree_maple.obj");

	//Herpetario
	Model HerpCueva((char*)"Models/Herpetario/Cueva/Cueva.obj");
	Model Pecera((char*)"Models/Herpetario/Cueva/cristalesPecera.obj");
	Model aguaHerp((char*)"Models/Herpetario/Cueva/agua.obj");
	Model rocaHerp((char*)"Models/Herpetario/Cueva/roca.obj");
	Model planta1Herp((char*)"Models/Herpetario/Cueva/plantas/plantas1.obj");
	Model planta2Herp((char*)"Models/Herpetario/Cueva/plantas/plantas2.obj");
	Model troncos1Herp((char*)"Models/Herpetario/Cueva/tronco/troncos1.obj");
	Model troncos2Herp((char*)"Models/Herpetario/Cueva/tronco/troncos2.obj");
	Model randall((char*)"Models/Herpetario/randall/randall.obj");
	Model mushu((char*)"Models/Herpetario/mushu/mushu.obj");
	Model cuerpoCoco((char*)"Models/Herpetario/crocodile/cocodrilo.obj");
	Model pataDerCoco((char*)"Models/Herpetario/crocodile/pataDer.obj");
	Model pataIzqCoco((char*)"Models/Herpetario/crocodile/pataIzq.obj");
	Model colaCoco((char*)"Models/Herpetario/crocodile/cola.obj");

	// Build and compile our shader program

	//Inicializaci�n de KeyFrames

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = frameX[i];
		KeyFrame[i].posY = frameY[i];
		KeyFrame[i].posZ = frameZ[i];
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotBicepDer = rBicepDer[i];
		KeyFrame[i].rotAnteDer = rAntebrazoDer[i];
		KeyFrame[i].rotManoDer = rManoDer[i];
		KeyFrame[i].rotIncBicepDer = 0;
		KeyFrame[i].rotIncAnteDer = 0;
		KeyFrame[i].rotIncManoDer = 0;

		KeyFrame[i].rotBicepIzq = rBicepIzq[i];
		KeyFrame[i].rotAnteIzq = rAntebrazoIzq[i];
		KeyFrame[i].rotManoIzq = rManoIzq[i];
		KeyFrame[i].rotIncBicepIzq = 0;
		KeyFrame[i].rotIncAnteIzq = 0;
		KeyFrame[i].rotIncManoIzq = 0;

		KeyFrame[i].rotCabeza = rCabeza[i];
		KeyFrame[i].rotIncCabeza = 0;
	}



	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacionMariposa();
		animCapibara();
		animCocodrilo();
		keyframeLion();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.3f, 0.3f, 0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.8f, 0.8f, 0.8f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.3f, 0.3f, 0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.8f, 0.8f, 0.8f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		//glBindTexture(GL_TEXTURE_2D, texture1);*/

		// Bind specular map
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);*/


		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp
		glm::mat4 tmp2 = glm::mat4(1.0f);

		view = camera.GetViewMatrix();


		//Carga de modelo 

		view = camera.GetViewMatrix();
		//Habitat de capibaras
		glm::mat4 model(1);
		//model = glm::translate(model, glm::vec3(posXCa, posYCa, posZCa));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//casaCapi.Draw(lightingShader);
		//barda.Draw(lightingShader);
		//rocas.Draw(lightingShader);
		//tina.Draw(lightingShader);

		//////Capybara anim

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXCa + movXCapibara, posYCa + movYCapibara, posZCa - movZCapibara));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotKitZ), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//capibara.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXCa + movXCapibara, posYCa + movYCapibara, posZCa - movZCapibara));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotKitZ), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(pataDelantera), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(-0.083, -0.158, 0.157));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//piernaDelanDer.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXCa + movXCapibara, posYCa + movYCapibara, posZCa - movZCapibara));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotKitZ), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(pataDelantera), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.102, -0.144, 0.165));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//piernaDelanIzq.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXCa + movXCapibara, posYCa + movYCapibara, posZCa - movZCapibara));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::rotate(model, glm::radians(pataTrasera), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotKitZ), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.086, -0.097, -0.349));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//piernaTraseIzq.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXCa + movXCapibara, posYCa + movYCapibara, posZCa - movZCapibara));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::rotate(model, glm::radians(pataTrasera), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotKitZ), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(-0.095, -0.112, -0.355));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//piernaTraseDer.Draw(lightingShader);

		// Mariposario
		//Estructura del domo
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//domo.Draw(lightingShader);
		//estructura.Draw(lightingShader);
		//banca.Draw(lightingShader);
		//
		////Banca1

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.2f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//banca.Draw(lightingShader);

		////Cuerpo de la mariposa
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::translate(model, glm::vec3(movKitX, 4.0f, movKitZ));
		//model = glm::rotate(model, glm::radians(rotMariposa), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//cuerpoMari.Draw(lightingShader);

		////Cuerpo de la mariposa 2
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//tmp2 = model = glm::translate(model, glm::vec3(1.6, 2.0f, 0.178));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//cuerpoMari.Draw(lightingShader);

		////Ala izquierda de la mariposa
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::translate(model, glm::vec3(movKitX + 0.001f, 4.0f, movKitZ));
		//model = glm::rotate(model, glm::radians(rotMariposa), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::rotate(model, glm::radians(rot1), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//alaIzq.Draw(lightingShader);

		////Ala derecha de la mariposa
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::translate(model, glm::vec3(movKitX-0.001f, 4.0f, movKitZ));
		//model = glm::rotate(model, glm::radians(rotMariposa), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 0.0f, -1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//alaDer.Draw(lightingShader);

		////Ala izquierda de la mariposa 2
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::translate(tmp2, glm::vec3(0.001f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rot1), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//alaIzq.Draw(lightingShader);

		////Ala derecha de la mariposa 2
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::translate(tmp2, glm::vec3(- 0.001f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 0.0f, -1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//alaDer.Draw(lightingShader);

		////Arbol 1
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//arbol.Draw(lightingShader);

		////Arbol 2
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::translate(model, glm::vec3(5.3f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//arbol.Draw(lightingShader);

		////Arbol 3
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::translate(model, glm::vec3(5.3f, 0.0f, -5.1f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//arbol.Draw(lightingShader);

		////Arbol 4
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.1f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//arbol.Draw(lightingShader);

		////Enviroment Draw
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviGrassPlane.Draw(lightingShader);
		//enviContorno.Draw(lightingShader);
		//enviRoad.Draw(lightingShader);
		//enviFrontFence.Draw(lightingShader);
		//enviBackFence.Draw(lightingShader);
		//enviGate.Draw(lightingShader);
		//enviLateralFence.Draw(lightingShader);
		//enviHerpFloor.Draw(lightingShader);

		//model = glm::translate(model, glm::vec3(159.910f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviLateralFence.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXEnvi + 18.37, posYEnvi, posZEnvi + 13.749));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(23.328f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(22.765f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(25.244f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -27.836f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-25.244f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-22.765f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-23.328f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(5.917f, 0.0f, -33.791f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(15.261f, 0.0f, 13.236f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(19.309f, 0.0f, -11.99f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(16.506f, 0.0f, -10.745f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 28.337f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(25.731f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -28.815f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(5.954f, 0.0f, 48.91f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 17.65f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-2.127f, 0.0f, 25.519f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-19.989f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-23.605f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-12.759f, 0.0f, 13.078f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-15.098f, 0.0f, -8.4f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-25.412f, 0.0f, -11.59f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-33.812f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-3.402f, 0.0f, -17.119f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -19.245f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -21.053f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -28.389f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(30.197f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 28.283f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLight.Draw(lightingShader);

		//Lion Habitat draw
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXLeones, posYLeones, posZLeones));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		lionRocks.Draw(lightingShader);
		lionFloor.Draw(lightingShader);
		lionExterior.Draw(lightingShader);
		lionFences.Draw(lightingShader);
		simba.Draw(lightingShader);
		scar.Draw(lightingShader);

		////Lion animation
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXLeones, posYLeones, posZLeones));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//tmp = model = glm::translate(model, glm::vec3(0.0f, 0.897f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//bodyLion.Draw(lightingShader);

		//model = glm::translate(tmp, glm::vec3(0.0f, 0.3f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//model = glm::rotate(model, glm::radians(rotCabeza), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//headLion.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(tmp, glm::vec3(0.187f, 0.054f, -0.011f));
		//model = glm::rotate(model, glm::radians(rotBicepDer), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//bicepDer.Draw(lightingShader);

		//model = glm::translate(model, glm::vec3(0.046f, -0.182f, -0.068f));
		//model = glm::rotate(model, glm::radians(rotAnteDer), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//antebrazoDer.Draw(lightingShader);

		//model = glm::translate(model, glm::vec3(0.026f, -0.2f, 0.048f));
		//model = glm::rotate(model, glm::radians(rotManoDer), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//manoDer.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(tmp, glm::vec3(-0.172f, 0.054f, -0.011f));
		//model = glm::rotate(model, glm::radians(rotBicepIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//bicepIzq.Draw(lightingShader);

		//model = glm::translate(model, glm::vec3(-0.068f, -0.2f, -0.026f));
		//model = glm::rotate(model, glm::radians(rotAnteIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//antebrazoIzq.Draw(lightingShader);

		//model = glm::translate(model, glm::vec3(-0.039f, -0.193f, 0.03f));
		//model = glm::rotate(model, glm::radians(rotManoIzq), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//manoIzq.Draw(lightingShader);

		////Panda habitat draw
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXPanda, posYPanda, posZPanda));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//pandaFloor.Draw(lightingShader);
		//pandaFence.Draw(lightingShader);
		//pandaChineseBuilding.Draw(lightingShader);
		//pandaRocks.Draw(lightingShader);
		//pandaWaterWell.Draw(lightingShader);

		////Penguin habitat draw
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXPenguin, posYPenguin, posZPenguin));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//penguinCenter.Draw(lightingShader);
		//penguinExternal.Draw(lightingShader);
		//penguinBowl.Draw(lightingShader);
		//penguinFloor.Draw(lightingShader);
		//penguinRailing.Draw(lightingShader);
		//penguinStreet.Draw(lightingShader);

		//Herpetario
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXHerp, posYHerp, posZHerp));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		HerpCueva.Draw(lightingShader);
		mushu.Draw(lightingShader);
		randall.Draw(lightingShader);
		troncos1Herp.Draw(lightingShader);
		troncos2Herp.Draw(lightingShader);
		rocaHerp.Draw(lightingShader);

		//crocodile herpetary
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXHerp + 1.706, posYHerp + 1.83 + movYCoco, posZHerp -0.968 + movCoco));
		model = glm::rotate(model, glm::radians(rotYCoco), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		cuerpoCoco.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(0.028,- 0.039,- 0.87));
		model = glm::rotate(model, glm::radians(rotColaCo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		colaCoco.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXHerp + 1.706 + 0.299, posYHerp + 1.83 - 0.011 + movYCoco, posZHerp - 0.968 + movCoco - 0.089));
		model = glm::rotate(model, glm::radians(rotYCoco), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPatasCo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pataIzqCoco.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXHerp+1.706-0.247, posYHerp+1.83+0.004+movYCoco, posZHerp-0.968+movCoco-0.067));
		model = glm::rotate(model, glm::radians(rotYCoco), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPatasCo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pataDerCoco.Draw(lightingShader);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		////Lion's water load
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXLeones, posYLeones + 0.01f, posZLeones));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.9f);
		//lionWater.Draw(lightingShader);
		
		////Cristales del domo
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		//cristales.Draw(lightingShader);

		////Foco de la lampara
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		//foco.Draw(lightingShader);

		////Cristales Capi 

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXCa, posYCa, posZCa));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		//cristalCasa.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXCa, posYCa, posZCa));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		//cristalesBarda.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXCa, posYCa, posZCa));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.9f);
		//aguaTina.Draw(lightingShader);

		////Penguin's water and cristals
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXPenguin, posYPenguin, posZPenguin));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.9f);
		//penguinWater.Draw(lightingShader);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		//penguinStreetGlass.Draw(lightingShader);

		//Herp Cristals
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXHerp, posYHerp, posZHerp));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		Pecera.Draw(lightingShader);
		aguaHerp.Draw(lightingShader);

		////Street Lights Glass
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXEnvi + 18.37, posYEnvi, posZEnvi + 13.749));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(23.328f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(22.765f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(25.244f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -27.836f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-25.244f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-22.765f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-23.328f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(5.917f, 0.0f, -33.791f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(15.261f, 0.0f, 13.236f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(19.309f, 0.0f, -11.99f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(16.506f, 0.0f, -10.745f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 28.337f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(25.731f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -28.815f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(5.954f, 0.0f, 48.91f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 17.65f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-2.127f, 0.0f, 25.519f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-19.989f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-23.605f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-12.759f, 0.0f, 13.078f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-15.098f, 0.0f, -8.4f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-25.412f, 0.0f, -11.59f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-33.812f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-3.402f, 0.0f, -17.119f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -19.245f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -21.053f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -28.389f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(30.197f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 28.283f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		//enviStreetLightGlass.Draw(lightingShader);


		glDisable(GL_BLEND);

		//Load transparency models for panda habitat
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXPanda, posYPanda, posZPanda));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//pandaBambuPlant.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//pandaBambuPlant.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//pandaBambuPlant.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(12.0f, 0.0f, -14.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//pandaBambuPlant.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(1.0f, 0.0f, -1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//pandaBambuPlant.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//pandaBambuPlant.Draw(lightingShader);

		//////Load transparency models for lions habitat
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXLeones, posYLeones, posZLeones));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//lionATree.Draw(lightingShader);
		//lionBTree.Draw(lightingShader);
		//lionCTree.Draw(lightingShader);

		////Load transparency models for herpetary
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXHerp, posYHerp, posZHerp));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		planta1Herp.Draw(lightingShader);
		planta2Herp.Draw(lightingShader);

		//////Draw enviroment trees
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posXEnvi + 29.074, posYEnvi, posZEnvi - 5.928));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-6.199f, 0.0f, 11.92f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(18.715f, 0.0f, -4.291f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(9.959f, 0.0f, -11.82f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(7.22f, 0.0f, -25.218f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-14.086f, 0.0f, -14.241f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-15.015f, 0.0f, 17.801f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(-8.259f, 0.0f, -38.84f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(8.978f, 0.0f, 102.348f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(12.712f, 0.0f, 13.818f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(17.318f, 0.0f, -14.37f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);
		//model = glm::translate(model, glm::vec3(12.528f, 0.0f, 12.896f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		//enviTree.Draw(lightingShader);

		glEnable(GL_DEPTH_TEST);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.02f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default




		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	/*glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);*/
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}


void keyframeLion() {
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotBicepDer += KeyFrame[playIndex].rotIncBicepDer;
			rotAnteDer += KeyFrame[playIndex].rotIncAnteDer;
			rotManoDer += KeyFrame[playIndex].rotIncManoDer;

			rotBicepIzq += KeyFrame[playIndex].rotIncBicepIzq;
			rotAnteIzq += KeyFrame[playIndex].rotIncAnteIzq;
			rotManoIzq += KeyFrame[playIndex].rotIncManoIzq;

			rotCabeza += KeyFrame[playIndex].rotIncCabeza;

			i_curr_steps++;
		}
	}
}

void animacionMariposa() {
	if (anim) {
		if (rot1 < 45.0f)
			rot1 += 3.0f;
		else {
			anim = false;
			anim2 = true;
		}
	}

	if (anim2) {
		if (rot1 > -45.0f)
			rot1 -= 3.0f;
		else {
			anim2 = false;
			anim = true;
		}
	}

	if (anim) {
		if (rot2 < 45.0f)
			rot2 += 3.0f;
		else {
			anim = false;
			anim2 = true;
		}
	}

	if (anim2) {
		if (rot2 > -45.0f)
			rot2 -= 3.0f;
		else {
			anim2 = false;
			anim = true;
		}
	}

	if (recorridoMariposa) {
		if (direccion) {
			movKitX -= 0.01f;
		}
		else {
			movKitX += 0.01f;
		}

		if (movKitX <= -1.0)
		{
			direccion = false;
			raiz = -1;
		}
		else if (movKitX >= 1.0) {
			direccion = true;
			raiz = 1;
		}
		float equisCuadrada = pow(movKitX, 2);
		if (equisCuadrada > 1 || equisCuadrada < -1) {
			equisCuadrada = 1;
		}
		movKitZ = raiz * sqrt(1 - equisCuadrada);
		rotMariposa = -57.296 * atan2(movKitZ, movKitX);
	}
}

void animCapibara() {
	if (recorridoCapibara)
	{
		if (animPatasDel)
		{
			if (pataTrasera < 15) {
				pataTrasera += 0.1;
				pataDelantera -= 0.1;
			}
			else {
				animPatasTras = true;
				animPatasDel = false;
			}
		}

		if (animPatasTras)
		{
			if (pataTrasera > 0) {
				pataTrasera -= 0.1;
				pataDelantera += 0.1;
			}
			else {
				animPatasTras = false;
				animPatasDel = true;
			}
		}

		if (recorrido1) {
			rotKit = -90.0f;
			movXCapibara -= 0.001f;
			if (movXCapibara < 11.0f)
			{
				recorrido2 = true;
				recorrido1 = false;
			}
		}

		if (recorrido2) {
			rotKit = -45.0f;
			movXCapibara -= 0.001f;
			movZCapibara -= 0.001f;
			if (movXCapibara < 9.5F) {
				recorrido3 = true;
				recorrido2 = false;
			}
		}

		if (recorrido3) {
			rotKit = -90.0f;
			rotKitZ = -22.0f;
			movXCapibara -= 0.001f;
			movYCapibara += 0.404f * 0.001f;
			if (movXCapibara < 5.5f) {
				recorrido3 = false;
				recorrido4 = true;
			}
		}

		if (recorrido4) {
			rotKitZ = 0.0f;
			movXCapibara -= 0.001f;
			if (movXCapibara < 3.0f) {
				recorrido4 = false;
				recorrido5 = true;
			}
		}

		if (recorrido5) {
			rotKit = 90.0f;
			movXCapibara += 0.001f;
			if (movXCapibara > 5.5f) {
				recorrido5 = false;
				recorrido6 = true;
			}
		}

		if (recorrido6) {
			rotKitZ = 22.0f;
			movXCapibara += 0.001f;
			movYCapibara -= 0.404f * 0.001f;
			if (movXCapibara > 9.5f) {
				recorrido6 = false;
				recorrido7 = true;
			}
		}

		if (recorrido7) {
			rotKitZ = 0.0f;
			rotKit = 135.0f;
			movXCapibara += 0.001f;
			movZCapibara += 0.001f;
			if (movXCapibara > 11.0F) {
				recorrido8 = true;
				recorrido7 = false;
			}
		}
		
		if (recorrido8) {
			rotKit = 90.0f;
			movXCapibara += 0.001f;
			if (movXCapibara > 13.5f)
			{
				recorrido1 = true;
				recorrido8 = false;
			}
		}
	}
}

void animCocodrilo() {
	if (recorridoCoco) {

		if (rotPatas1) {
			if (rotPatasCo < 20) {
				rotPatasCo += 0.1;
			}
			else {
				rotPatas1 = false;
				rotPatas2 = true;
			}
		}

		if (rotPatas2) {
			if (rotPatasCo > 0) {
				rotPatasCo -= 0.1;
			}
			else {
				rotPatas1 = true;
				rotPatas2 = false;
			}
		}

		if (rotCola1) {
			if (rotColaCo < 20) {
				rotColaCo += 0.1;
			}
			else {
				rotCola1 = false;
				rotCola2 = true;
			}
		}

		if (rotCola2) {
			if (rotColaCo > -20) {
				rotColaCo -= 0.1;
			}
			else {
				rotCola1 = true;
				rotCola2 = false;
			}
		}

		rotYCoco = -20;
		movYCoco += 0.3639*0.001;
		movCoco += 0.001;
		if (movCoco > 1.5) {
			recorridoCoco = false;
		}
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (keys[GLFW_KEY_L])
	{
		if (play == false && FrameIndex > 1)
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}


	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}


	if (keys[GLFW_KEY_Z])
	{
		recorridoMariposa = !recorridoMariposa;
		anim = !anim;
	}

	if (keys[GLFW_KEY_C])
	{
		recorridoCapibara = true;
		animPatasDel = !animPatasDel;
	}

	if (keys[GLFW_KEY_B])
	{
		recorridoCoco = !recorridoCoco;
		rotPatas1 = !rotPatas1;
		rotCola1 = !rotCola1;
	}

}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	if (keys[GLFW_KEY_1])
	{

		movCamera = 0.01f;//Manda una velocidad de 0.01 a la camara automatica

	}

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}