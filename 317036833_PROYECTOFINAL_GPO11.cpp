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
void animacionPinguinos();
void animacionPanda();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(-52.0f, 5.0f, 25.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
float movCamera = 0.0f;
int raiz = 1;
float rot1 = 0.0f;
float rot2 = 0.0f;
float movKitX = 0.0f;
float movKitZ = 1.0f;
float rotMariposa = -90.0;
bool anim = false;
bool anim2 = false;
bool direccion = true;
bool recorridoMariposa = false;

//Penguin Animation variables
float initRotation = 90.0f;
float rotPaSkiper = 0.0f;
float rotXSkiperIzq = 0.0f;
float rotZSkiperIzq = 0.0f;
float rotYSkiperIzq = 0.0f;
float rotXSkiperDer = 0.0f;
float rotZSkiperDer = 0.0f;
float rotYSkiperDer = 0.0f;
float rotPSkiper = 90.0f;
float trasYSkiper = 0.0f;
float rotXKowalskiDer = 0.0f;
float rotZKowalskiDer = 0.0f;
float rotYKowalskiDer = 0.0f;
float rotXRicoIzq = 0.0f;
float rotZRicoIzq = 0.0f;
float rotYRicoIzq = 0.0f;
bool animPenguin = false;
bool route1 = true;
bool route2 = false;
bool route3 = false;
bool route4 = false;
bool route5 = false;
bool route6 = false;
bool route7 = false;

//Panda's animation variables
bool animPanda = false;

float pandaBicepDerRotX = 0.0f;
float pandaBicepDerRotY = 0.0f;
float pandaBicepDerRotZ = 0.0f;
float pandaBicepIzqRotX = 0.0f;
float pandaBicepIzqRotY = 0.0f;
float pandaBicepIzqRotZ = 0.0f;

float pandaAntebrazoDerRotX = 0.0f;
float pandaAntebrazoDerRotY = 0.0f;
float pandaAntebrazoDerRotZ = 0.0f;
float pandaAntebrazoIzqRotX = 0.0f;
float pandaAntebrazoIzqRotY = 0.0f;
float pandaAntebrazoIzqRotZ = 0.0f;

float pandaManoDerRotX = 0.0f;
float pandaManoDerRotY = 0.0f;
float pandaManoDerRotZ = 0.0f;
float pandaManoIzqRotX = 0.0f;
float pandaManoIzqRotY = 0.0f;
float pandaManoIzqRotZ = 0.0f;

float pandaPiernaDerRotX = 0.0f;
float pandaPiernaDerRotY = 0.0f;
float pandaPiernaDerRotZ = 0.0f;
float pandaPiernaIzqRotX = 0.0f;
float pandaPiernaIzqRotY = 0.0f;
float pandaPiernaIzqRotZ = 0.0f;

bool part1 = true;
bool part2 = false;
bool part3 = false;
bool part4 = false;
bool part5 = false;
bool part6 = false;
bool part7 = false;
bool part8 = false;
bool part9 = false;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

bool active;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Keyframes
float posXCa = PosIni.x + 84.22f, posYCa = PosIni.y, posZCa = PosIni.z + 44.191f;
float posXMari = PosIni.x - 3.0f, posYMari = PosIni.y, posZMari = PosIni.z + 44.768f;

float posXLeones = PosIni.x - 13.277, posYLeones = PosIni.y - 3.134, posZLeones = PosIni.z - 44.467;
float posXPanda = PosIni.x + 86.652f, posYPanda = PosIni.y, posZPanda = PosIni.z - 43.570;
float posXPenguin = PosIni.x, posYPenguin = PosIni.y - 5.535, posZPenguin = PosIni.z;
float posXHerp = PosIni.x + 74.816, posYHerp = PosIni.y, posZHerp = PosIni.z;
float posXEnvi = PosIni.x, posYEnvi = PosIni.y, posZEnvi = PosIni.z;

#define MAX_FRAMES 9
int i_max_steps = 190;
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




//void saveFrame(void)
//{
//	KeyFrame[FrameIndex].posX = posX;
//	KeyFrame[FrameIndex].posY = posY;
//	KeyFrame[FrameIndex].posZ = posZ;
//	
//	KeyFrame[FrameIndex].rotBicep = rotBicep;
//	KeyFrame[FrameIndex].rotAntebrazo = rotAntebrazo;
//	KeyFrame[FrameIndex].rotMano = rotMano;
//	
//	printf("Frame %d: (posx %f,posy %f,posz %f)\n", FrameIndex, KeyFrame[FrameIndex].posX, KeyFrame[FrameIndex].posY, KeyFrame[FrameIndex].posZ);
//	printf("Frame %d: (Bicep %f,Antebrazo %f,Mano %f)\n", FrameIndex, KeyFrame[FrameIndex].rotBicep, KeyFrame[FrameIndex].rotAntebrazo, KeyFrame[FrameIndex].rotMano);
//	FrameIndex++;
//}

//void resetElements(void)
//{
//	posX = KeyFrame[0].posX;
//	posY = KeyFrame[0].posY;
//	posZ = KeyFrame[0].posZ;
//
//	rotBicep = KeyFrame[0].rotBicep;
//	rotAntebrazo = KeyFrame[0].rotAntebrazo;
//	rotMano = KeyFrame[0].rotMano;
//}
//
//void interpolation(void)
//{
//
//	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
//	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
//	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
//	
//	KeyFrame[playIndex].rotIncBicep = (KeyFrame[playIndex + 1].rotBicep - KeyFrame[playIndex].rotBicep) / i_max_steps;
//	KeyFrame[playIndex].rotIncAnte = (KeyFrame[playIndex + 1].rotAntebrazo - KeyFrame[playIndex].rotAntebrazo) / i_max_steps;
//	KeyFrame[playIndex].rotIncMano = (KeyFrame[playIndex + 1].rotMano - KeyFrame[playIndex].rotMano) / i_max_steps;
//
//}




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

	//Carga de modelos del mariposario
	Model domo((char*)"Models/Mariposario/Domo/Domo.obj");
	Model cristales((char*)"Models/Mariposario/Domo/CristalesDomo.obj");
	Model estructura((char*)"Models/Mariposario/Street_lamp/estructura.obj");
	Model foco((char*)"Models/Mariposario/Street_lamp/foco.obj");
	Model banca((char*)"Models/Mariposario/Bank/Bank.obj");
	Model arbol((char*)"Models/Mariposario/tree/tree.obj");
	Model cuerpoMari((char*)"Models/Mariposario/Butterfly/body.obj");
	Model alaIzq((char*)"Models/Mariposario/Butterfly/wing_left.obj");
	Model alaDer((char*)"Models/Mariposario/Butterfly/wing_right.obj");

	//Carga de modelos de capibaras
	Model casaCapi((char*)"Models/Capibaras/caseta/CasaDescanso.obj");
	Model cristalCasa((char*)"Models/Capibaras/caseta/Cristal.obj");
	Model barda((char*)"Models/Capibaras/habitat/Barda.obj");
	Model cristalesBarda((char*)"Models/Capibaras/habitat/Cristales.obj");
	Model planta((char*)"Models/Capibaras/habitat/plantas.obj");
	Model rocas((char*)"Models/Capibaras/RocasAmbiente/rocas.obj");
	Model tina((char*)"Models/Capibaras/tina/Tina.obj");
	Model aguaTina((char*)"Models/Capibaras/tina/Agua.obj");
	
	//Lion's habitat model load
	Model lionFloor((char*)"Models/HabitatLeones/FloorModel/FloorPlane.obj");
	Model lionRocks((char*)"Models/HabitatLeones/RockCollection/Rocks.obj");
	Model lionWater((char*)"Models/HabitatLeones/WaterLakeModel/WaterPlane.obj");
	Model lionATree((char*)"Models/HabitatLeones/Tree/ATree.obj");
	Model lionBTree((char*)"Models/HabitatLeones/Tree/BTree.obj");
	Model lionCTree((char*)"Models/HabitatLeones/Tree/CTree.obj");
	Model lionFences((char*)"Models/HabitatLeones/FencesModel/FenceModel.obj");
	Model lionExterior((char*)"Models/HabitatLeones/ConcreteExterior/BaseExterior.obj");

	//Panda's habitat model load
	Model pandaFloor((char*)"Models/HabitatPanda/GrassPlane/GrassPlane.obj");
	Model pandaRocks((char*)"Models/HabitatPanda/Rocks/Rock.obj");
	Model pandaFence((char*)"Models/HabitatPanda/FenceModel/FenceModel.obj");
	Model pandaChineseBuilding((char*)"Models/HabitatPanda/ChineseBuilding/ChineseBuilding.obj");
	Model pandaBambuPlant((char*)"Models/HabitatPanda/BambuPlant/BambuPlant.obj");
	Model pandaWaterWell((char*)"Models/HabitatPanda/WaterWallModel/WaterWell.obj");
	Model pandaBody((char*)"Models/HabitatPanda/Po_Panda/Po.obj");
	Model pandaBicepIzq((char*)"Models/HabitatPanda/Po_Panda/BicepIzq.obj");
	Model pandaBicepDer((char*)"Models/HabitatPanda/Po_Panda/BicepDer.obj");
	Model pandaAntebrazoIzq((char*)"Models/HabitatPanda/Po_Panda/AntebrazoIzq.obj");
	Model pandaAntebrazoDer((char*)"Models/HabitatPanda/Po_Panda/AntebrazoDer.obj");
	Model pandaManoIzq((char*)"Models/HabitatPanda/Po_Panda/ManoIzq.obj");
	Model pandaManoDer((char*)"Models/HabitatPanda/Po_Panda/ManoDer.obj");
	Model pandaPiernaIzq((char*)"Models/HabitatPanda/Po_Panda/PataIzq.obj");
	Model pandaPiernaDer((char*)"Models/HabitatPanda/Po_Panda/PataDer.obj");

	//Penguin's habitat models load
	Model penguinCenter((char*)"Models/HabitatPinguinos/CentralBaseModel/Center.obj");
	Model penguinExternal((char*)"Models/HabitatPinguinos/ExternalBaseModel/ExternalBaseModel.obj");
	Model penguinFloor((char*)"Models/HabitatPinguinos/FloorModel/Floor.obj");
	Model penguinBowl((char*)"Models/HabitatPinguinos/PenguinBowlModel/Bowl.obj");
	Model penguinRailing((char*)"Models/HabitatPinguinos/RailingModel/RailingModel.obj");
	Model penguinStreet((char*)"Models/HabitatPinguinos/StreetLampModel/StreetLamp.obj");
	Model penguinStreetGlass((char*)"Models/HabitatPinguinos/StreetLampModel/StreetLampGlass.obj");
	Model penguinWater((char*)"Models/HabitatPinguinos/WaterPlane/Water.obj");
	Model cabo((char*)"Models/HabitatPinguinos/PenguinModels/CaboModel/Cabo.obj");
	Model caboADer((char*)"Models/HabitatPinguinos/PenguinModels/CaboModel/CaboAletaDerecha.obj");
	Model caboAIzq((char*)"Models/HabitatPinguinos/PenguinModels/CaboModel/CaboAletaIzquierda.obj");
	Model kowaslki((char*)"Models/HabitatPinguinos/PenguinModels/KowalskiModel/Kowalski.obj");
	Model kowaslkiADer((char*)"Models/HabitatPinguinos/PenguinModels/KowalskiModel/KowalskiADer.obj");
	Model kowaslkiAIzq((char*)"Models/HabitatPinguinos/PenguinModels/KowalskiModel/KowalskiAIzq.obj");
	Model rico((char*)"Models/HabitatPinguinos/PenguinModels/RicoModel/Rico.obj");
	Model ricoADer((char*)"Models/HabitatPinguinos/PenguinModels/RicoModel/RicoADer.obj");
	Model ricoAIzq((char*)"Models/HabitatPinguinos/PenguinModels/RicoModel/RicoAIzq.obj");
	Model skiper((char*)"Models/HabitatPinguinos/PenguinModels/SkiperModel/Skiper.obj");
	Model skiperADer((char*)"Models/HabitatPinguinos/PenguinModels/SkiperModel/SkiperADer.obj");
	Model skiperAIzq((char*)"Models/HabitatPinguinos/PenguinModels/SkiperModel/SkiperAIzq.obj");
	Model skiperPDer((char*)"Models/HabitatPinguinos/PenguinModels/SkiperModel/SkiperPDer.obj");
	Model skiperPIzq((char*)"Models/HabitatPinguinos/PenguinModels/SkiperModel/SkiperPIzq.obj");

	//Enviroment's models load
	Model enviGrassPlane((char*)"Models/Entorno/GrassPlane/GrassPlane.obj");
	Model enviContorno((char*)"Models/Entorno/ConcreteLimit/Contorno.obj");
	Model enviGate((char*)"Models/Entorno/Gate/wooden_gate.obj");
	Model enviRoad((char*)"Models/Entorno/Road/Road.obj");
	Model enviFrontFence((char*)"Models/Entorno/Fence/FrontFence.obj");
	Model enviBackFence((char*)"Models/Entorno/Fence/BackFence.obj");
	Model enviLateralFence((char*)"Models/Entorno/Fence/LateralFence.obj");
	Model enviHerpFloor((char*)"Models/Herpetario/Floor/Floor.obj");
	Model enviStreetLight((char*)"Models/Entorno/StreetLight/StreetLight.obj");
	Model enviStreetLightGlass((char*)"Models/Entorno/StreetLight/StreetLightGlass.obj");
	Model enviTree((char*)"Models/Entorno/tree/tree_maple.obj");
	Model enviBank((char*)"Models/Entorno/Bank/Bank.obj");

	//Herpetario
	Model HerpCueva((char*)"Models/Herpetario/Cueva/Cueva.obj");
	Model Pecera((char*)"Models/Herpetario/Cueva/cristalesPecera.obj");


	// Build and compile our shader program

	//Inicializaci�n de KeyFrames

	/*for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = frameX[i];
		KeyFrame[i].posY = frameY[i];
		KeyFrame[i].posZ = frameZ[i];
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotBicep = rBicep[i];
		KeyFrame[i].rotAntebrazo = rAntebrazo[i];
		KeyFrame[i].rotMano = rMano[i];
		KeyFrame[i].rotIncBicep = 0;
		KeyFrame[i].rotIncAnte = 0;
		KeyFrame[i].rotIncMano = 0;
	}*/



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
		animacionPinguinos();
		animacionPanda();


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
		glm::mat4 tmpPanda = glm::mat4(1.0f); //Temp for Po
		glm::mat4 tmpCabo = glm::mat4(1.0f); //Temp for Cabo
		glm::mat4 tmpKowalski = glm::mat4(1.0f); //Temp for Kowalski
		glm::mat4 tmpRico = glm::mat4(1.0f); //Temp for Rico
		glm::mat4 tmpSkiper = glm::mat4(1.0f);	//Temp for Skiper

		view = camera.GetViewMatrix();


		//Carga de modelo 

		view = camera.GetViewMatrix();
		//Habitat de capibaras
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(posXCa, posYCa, posZCa));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		casaCapi.Draw(lightingShader);
		barda.Draw(lightingShader);
		rocas.Draw(lightingShader);
		tina.Draw(lightingShader);

		// Mariposario
		//Estructura del domo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		domo.Draw(lightingShader);
		estructura.Draw(lightingShader);
		banca.Draw(lightingShader);
		
		//Banca1
		/*model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		banca.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.2f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		banca.Draw(lightingShader);*/

		//Arbol 1
		//model = glm::mat4(1);
		////model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//arbol.Draw(lightingShader);

		//Arbol 2
		//model = glm::mat4(1);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		/*model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		model = glm::translate(model, glm::vec3(5.3f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		arbol.Draw(lightingShader);*/

		////Cuerpo de la mariposa
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::translate(model, glm::vec3(5.0f, 0.0f, -5.0f));
		//model = glm::translate(model, glm::vec3(movKitX, 2.0f, movKitZ));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, glm::radians(rotMariposa), glm::vec3(0.0f, 1.0f, 0.0));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//cuerpoMari.Draw(lightingShader);

		////Cuerpo de la mariposa 2
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::translate(model, glm::vec3(5.0f, 0.0f, -5.0f));
		//tmp2 = model = glm::translate(model, glm::vec3(1.6, 2.0f, 0.178));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//cuerpoMari.Draw(lightingShader);

		////Ala izquierda de la mariposa
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::translate(model, glm::vec3(5.0f, 0.0f, -5.0f));
		//model = glm::translate(model, glm::vec3(movKitX + 0.001f, 4.0f, movKitZ));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, glm::radians(rotMariposa), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::rotate(model, glm::radians(rot1), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//alaIzq.Draw(lightingShader);

		////Ala derecha de la mariposa
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::translate(model, glm::vec3(5.0f, 0.0f, -5.0f));
		//model = glm::translate(model, glm::vec3(movKitX-0.001f, 4.0f, movKitZ));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, glm::radians(rotMariposa), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 0.0f, -1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//alaDer.Draw(lightingShader);

		////Ala izquierda de la mariposa 2
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::translate(tmp2, glm::vec3(0.001f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rot1), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//alaIzq.Draw(lightingShader);

		////Ala derecha de la mariposa 2
		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::translate(tmp2, glm::vec3(- 0.001f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 0.0f, -1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		//alaDer.Draw(lightingShader);
		//alas.Draw(lightingShader);*/

		//Enviroment Draw
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviGrassPlane.Draw(lightingShader);
		enviContorno.Draw(lightingShader);
		enviRoad.Draw(lightingShader);
		enviFrontFence.Draw(lightingShader);
		enviBackFence.Draw(lightingShader);
		enviGate.Draw(lightingShader);
		enviLateralFence.Draw(lightingShader);
		enviHerpFloor.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(159.910f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviLateralFence.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 18.37, posYEnvi, posZEnvi + 13.749));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(23.328f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(22.765f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(25.244f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -27.836f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-25.244f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-22.765f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-23.328f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.917f, 0.0f, -33.791f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(15.261f, 0.0f, 13.236f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(19.309f, 0.0f, -11.99f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(16.506f, 0.0f, -10.745f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 28.337f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(25.731f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -28.815f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.954f, 0.0f, 48.91f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 17.65f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-2.127f, 0.0f, 25.519f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-19.989f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-23.605f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-12.759f, 0.0f, 13.078f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-15.098f, 0.0f, -8.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-25.412f, 0.0f, -11.59f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-33.812f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-3.402f, 0.0f, -17.119f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -19.245f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -21.053f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -28.389f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(30.197f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 28.283f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLight.Draw(lightingShader);

		//enviroment banks draw
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 18.46, posYEnvi, posZEnvi + 10.864));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.641));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.765));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(8.875f, 0.0f, -3.003));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.076f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.076f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.076f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.076f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -15.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(3.573f, 0.0f, -7.339f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.371f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.117f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(13.759f, 0.0f, -4.459f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -15.568f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -13.849f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -13.54f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -12.307f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-14.616f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -29.419f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -16.094f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -16.094f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -16.094f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-8.802f, 0.0f, -8.981f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.559f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -17.818f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-37.338f, 0.0f, -10.418f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -16.096f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -16.096f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -16.096f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -16.096f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-6.056f, 0.0f, -34.508f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -21.254f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -18.922f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-7.443f, 0.0f, -8.161f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -25.11f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		enviBank.Draw(lightingShader);

		//Lion Habitat draw
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXLeones, posYLeones, posZLeones));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		lionRocks.Draw(lightingShader);
		lionFloor.Draw(lightingShader);
		lionExterior.Draw(lightingShader);
		lionFences.Draw(lightingShader);

		//Panda habitat draw
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXPanda, posYPanda, posZPanda));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaFloor.Draw(lightingShader);
		pandaFence.Draw(lightingShader);
		pandaChineseBuilding.Draw(lightingShader);
		pandaRocks.Draw(lightingShader);
		pandaWaterWell.Draw(lightingShader);

		//Po herarchy
		//Body draw
		model = glm::mat4(1);
		tmpPanda = model = glm::translate(model, glm::vec3(87.785f, 1.0f, -38.276f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaBody.Draw(lightingShader);
		//Right Bicep Draw
		model = glm::translate(tmpPanda, glm::vec3( -0.4f, 0.35f, -0.07f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaBicepDerRotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaBicepDerRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(45.0f - pandaBicepDerRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaBicepDer.Draw(lightingShader);
		//Right Forearm Draw
		model = glm::translate(model, glm::vec3(-0.303f, -0.065f, 0.0f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaAntebrazoDerRotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaAntebrazoDerRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaAntebrazoDerRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaAntebrazoDer.Draw(lightingShader);
		//Right Hand Draw
		model = glm::translate(model, glm::vec3(-0.47f, 0.011f, 0.014f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaManoDerRotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaManoDerRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaManoDerRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaManoDer.Draw(lightingShader);
		//Left Bicep Draw
		model = glm::translate(tmpPanda, glm::vec3(0.45f, 0.35f, -0.065f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaBicepIzqRotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaBicepIzqRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-45.0f + pandaBicepIzqRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaBicepIzq.Draw(lightingShader);
		//Left Forearm Draw
		model = glm::translate(model, glm::vec3(0.331f, -0.055f, -0.01f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaAntebrazoIzqRotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaAntebrazoIzqRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaAntebrazoIzqRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaAntebrazoIzq.Draw(lightingShader);
		//Left Hand Draw
		model = glm::translate(model, glm::vec3(0.47f, -0.015f, 0.029f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaManoIzqRotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaManoIzqRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaManoIzqRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaManoIzq.Draw(lightingShader);
		//Right Leg Draw
		model = glm::translate(tmpPanda, glm::vec3(-0.265f, -0.556f, 0.069f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaPiernaDerRotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaPiernaDerRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaPiernaDerRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaPiernaDer.Draw(lightingShader);
		//Left Leg Draw
		model = glm::translate(tmpPanda, glm::vec3(0.207f, -0.559f, 0.027f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaPiernaIzqRotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaPiernaIzqRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pandaPiernaIzqRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		pandaPiernaIzq.Draw(lightingShader);

		//Penguin habitat draw
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXPenguin, posYPenguin, posZPenguin));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		penguinCenter.Draw(lightingShader);
		penguinExternal.Draw(lightingShader);
		penguinBowl.Draw(lightingShader);
		penguinFloor.Draw(lightingShader);
		penguinRailing.Draw(lightingShader);
		penguinStreet.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		penguinStreet.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -23.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		penguinStreet.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		penguinStreet.Draw(lightingShader);

		//Penguins Draw
		//Cabo Herarchy
		//Body
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmpCabo = model = glm::translate(model, glm::vec3(-2.0, 2.4f, 0.0f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cabo.Draw(lightingShader);
		//Right Fin
		view = camera.GetViewMatrix();
		model = glm::translate(tmpCabo, glm::vec3(0.2f, 0.45f, -0.3f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		caboADer.Draw(lightingShader);
		//Left Fin
		view = camera.GetViewMatrix();
		model = glm::translate(tmpCabo, glm::vec3(0.2f, 0.45f, 0.3f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(55.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		caboAIzq.Draw(lightingShader);
		//Kowalski Herarchy
		//Body
		model = glm::mat4(1);
		tmpKowalski = model = glm::translate(model, glm::vec3(2.0, 2.8f, -2.0f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(-initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		kowaslki.Draw(lightingShader);
		//Right Fin
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 2.0f, posYEnvi + 2.8f, posZEnvi - 2.0f));
		model = glm::rotate(model, glm::radians(-initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.3f, 0.6f, -0.1f));
		model = glm::rotate(model, glm::radians(-55.0f + rotZKowalskiDer), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotXKowalskiDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotYKowalskiDer), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		kowaslkiADer.Draw(lightingShader);
		//Left Fin
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 2.0f, posYEnvi + 2.8f, posZEnvi - 2.0f));
		model = glm::rotate(model, glm::radians(-initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.3f, 0.6f, -0.1f));
		model = glm::rotate(model, glm::radians(55.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		kowaslkiAIzq.Draw(lightingShader);
		//Rico Herarchy
		//Body
		model = glm::mat4(1);
		tmpRico = model = glm::translate(model, glm::vec3(2.0, 2.6f, 2.0f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(-initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		rico.Draw(lightingShader);
		//Right Fin
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 2.0f, posYEnvi + 2.6f, posZEnvi + 2.0f));
		model = glm::rotate(model, glm::radians(-initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.4f, 0.6f, -0.1f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		ricoADer.Draw(lightingShader);
		//Left Fin
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 2.0f, posYEnvi + 2.6f, posZEnvi + 2.0f));
		model = glm::rotate(model, glm::radians(-initRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.4f, 0.6f, -0.1f));
		model = glm::rotate(model, glm::radians(55.0f - rotZRicoIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotXRicoIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotYRicoIzq), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		ricoAIzq.Draw(lightingShader);
		//Skiper Herarchy
		//Body
		model = glm::mat4(1);
		tmpSkiper = model = glm::translate(model, glm::vec3(2.2, 2.45f + trasYSkiper, 0.0f));
		model = glm::translate(model, glm::vec3(posXEnvi, posYEnvi, posZEnvi));
		model = glm::rotate(model, glm::radians(-rotPSkiper), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		skiper.Draw(lightingShader);
		//Right Fin
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 2.2f, posYEnvi + 2.45f, posZEnvi));
		model = glm::rotate(model, glm::radians(-rotPSkiper), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.4f, 0.45f + trasYSkiper, 0.25f));
		model = glm::rotate(model, glm::radians(-55.0f + rotZSkiperDer), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotXSkiperDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotYSkiperDer), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		skiperADer.Draw(lightingShader);
		//Left Fin
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 2.2f, posYEnvi + 2.45f, posZEnvi));
		model = glm::rotate(model, glm::radians(-rotPSkiper), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.4f, 0.45f + trasYSkiper, 0.25f));
		model = glm::rotate(model, glm::radians(55.0f - rotZSkiperIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotXSkiperIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotYSkiperIzq), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		skiperAIzq.Draw(lightingShader);
		//Right Leg
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 2.2f, posYEnvi + 2.45f, posZEnvi));
		model = glm::rotate(model, glm::radians(-rotPSkiper), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.3f, -1.0f + trasYSkiper, 0.25f));
		model = glm::rotate(model, glm::radians(rotPaSkiper), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		skiperPDer.Draw(lightingShader);
		//Left Leg
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 2.2f, posYEnvi + 2.45f, posZEnvi));
		model = glm::rotate(model, glm::radians(-rotPSkiper), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.3f, -1.0f + trasYSkiper, 0.25f));
		model = glm::rotate(model, glm::radians(rotPaSkiper), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		skiperPIzq.Draw(lightingShader);

		//Herpetario
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXHerp, posYHerp, posZHerp));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		HerpCueva.Draw(lightingShader);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Lion's water load
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXLeones, posYLeones + 0.01f, posZLeones));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.9f);
		lionWater.Draw(lightingShader);
		
		//Cristales del domo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		cristales.Draw(lightingShader);

		//Foco de la lampara
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXMari, posYMari, posZMari));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		foco.Draw(lightingShader);

		//Cristales Capi 

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXCa, posYCa, posZCa));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		cristalCasa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXCa, posYCa, posZCa));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		cristalesBarda.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXCa, posYCa, posZCa));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.406f, 1.406f, 1.406f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.9f);
		aguaTina.Draw(lightingShader);

		//Penguin's water and cristals
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXPenguin, posYPenguin, posZPenguin));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.9f);
		penguinWater.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		penguinStreetGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.75);
		penguinStreetGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -23.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.75);
		penguinStreetGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.75);
		penguinStreetGlass.Draw(lightingShader);

		//Herp Cristals
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXHerp, posYHerp, posZHerp));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		Pecera.Draw(lightingShader);

		//Street Lights Glass
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 18.37, posYEnvi, posZEnvi + 13.749));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(23.328f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(22.765f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(25.244f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -27.836f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-25.244f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-22.765f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-23.328f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.917f, 0.0f, -33.791f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(15.261f, 0.0f, 13.236f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(19.309f, 0.0f, -11.99f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(16.506f, 0.0f, -10.745f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 28.337f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(25.731f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -28.815f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.954f, 0.0f, 48.91f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 17.65f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-2.127f, 0.0f, 25.519f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-19.989f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-23.605f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-12.759f, 0.0f, 13.078f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-15.098f, 0.0f, -8.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-25.412f, 0.0f, -11.59f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-33.812f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-3.402f, 0.0f, -17.119f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -19.245f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -21.053f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -28.389f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(30.197f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 28.283f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0);
		enviStreetLightGlass.Draw(lightingShader);



		glDisable(GL_BLEND);

		//Load transparency models for panda habitat
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXPanda, posYPanda, posZPanda));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		pandaBambuPlant.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pandaBambuPlant.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pandaBambuPlant.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(12.0f, 0.0f, -14.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pandaBambuPlant.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pandaBambuPlant.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pandaBambuPlant.Draw(lightingShader);

		//Load transparency models for lions habitat
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXLeones, posYLeones, posZLeones));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		lionATree.Draw(lightingShader);
		lionBTree.Draw(lightingShader);
		lionCTree.Draw(lightingShader);

		//Draw enviroment trees
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posXEnvi + 29.074, posYEnvi, posZEnvi - 5.928));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-6.199f, 0.0f, 11.92f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(18.715f, 0.0f, -4.291f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(9.959f, 0.0f, -11.82f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(7.22f, 0.0f, -25.218f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-14.086f, 0.0f, -14.241f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-15.015f, 0.0f, 17.801f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-8.259f, 0.0f, -38.84f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(8.978f, 0.0f, 102.348f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(12.712f, 0.0f, 13.818f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(17.318f, 0.0f, -14.37f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(12.528f, 0.0f, 12.896f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1.0);
		enviTree.Draw(lightingShader);

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


//void keyframePersona() {
//	if (play)
//	{
//		if (i_curr_steps >= i_max_steps) //end of animation between frames?
//		{
//			playIndex++;
//			if (playIndex > FrameIndex - 2)	//end of total animation?
//			{
//				printf("termina anim\n");
//				playIndex = 0;
//				play = false;
//			}
//			else //Next frame interpolations
//			{
//				i_curr_steps = 0; //Reset counter
//				//Interpolation
//				interpolation();
//			}
//		}
//		else
//		{
//			//Draw animation
//			posX += KeyFrame[playIndex].incX;
//			posY += KeyFrame[playIndex].incY;
//			posZ += KeyFrame[playIndex].incZ;
//
//			rotBicep += KeyFrame[playIndex].rotIncBicep;
//			rotAntebrazo += KeyFrame[playIndex].rotIncAnte;
//
//			rotMano += KeyFrame[playIndex].rotIncMano;
//
//			i_curr_steps++;
//		}
//	}
//}

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

void animacionPinguinos() {
	if (animPenguin) {
		if (route1) {
			rotZSkiperDer += 0.2f;
			rotZRicoIzq += 0.2f;
			if (rotZSkiperDer > 90.0f) {
				route1 = false;
				route2 = true;
			}
		}
		if (route2) {
			if (rotZRicoIzq > 0.0f)
				rotZRicoIzq -= 0.2f;
			if (rotXSkiperDer < 90.0f) {
				rotXSkiperDer += 0.2f;
				rotXKowalskiDer += 0.2f;
			}
			if (rotZKowalskiDer < 90.0f)
				rotZKowalskiDer += 0.2f;
			rotPSkiper -= 0.2f;
			if (trasYSkiper < 1.0)
				trasYSkiper += 0.002;
			if (rotPSkiper < -100.0f) {
				route2 = false;
				route3 = true;
			}
		}
		if (route3) {
			if (rotZRicoIzq < 90.0f)
				rotZRicoIzq += 0.2f;
			if (rotXRicoIzq < 90.0f) {
				rotXRicoIzq += 0.2f;
				rotXKowalskiDer -= 0.2f;
			}
			if (rotZKowalskiDer < 90.0f)
				rotZKowalskiDer += 0.2f;
			rotPSkiper -= 0.2f;
			if (trasYSkiper > 0.0)
				trasYSkiper -= 0.002;
			if (rotPSkiper < -280.0f) {
				route3 = false;
				route4 = true;
			}
		}
		if (route4) {
			if (rotZSkiperIzq < 90.0f) {
				rotZSkiperIzq += 0.2f;
				rotZSkiperDer -= 0.2f;
				rotZKowalskiDer -= 0.2;
			}
			if (rotXSkiperIzq < 90.0f) {
				rotXSkiperIzq += 0.2f;
				rotXKowalskiDer += 0.2f;
			}
			rotPSkiper += 0.2f;
			if (rotPSkiper > -90.0f) {
				route4 = false;
				route5 = true;
			}
		}
		if (route5) {
			if (rotXSkiperDer > 0.0f) {
				rotXSkiperDer -= 0.2f;
				rotXSkiperIzq -= 0.2f;
				rotXKowalskiDer -= 0.2f;
				rotXRicoIzq -= 0.2f;

			}
			if (rotZSkiperDer < 90.0f)
				rotZSkiperDer += 0.2f;
			if (rotZKowalskiDer < 30.0f)
				rotZKowalskiDer += 0.2f;
			if (rotZRicoIzq > 30.0f)
				rotZRicoIzq -= 0.2f;
			if (rotYKowalskiDer < 45.0f) {
				rotYRicoIzq -= 0.2f;
				rotYKowalskiDer += 0.2f;
				rotYSkiperDer += 0.2f;
				rotYSkiperIzq -= 0.2f;
			}
			rotPSkiper += 0.2f;
			if (rotPSkiper > 90.0f) {
				route5 = false;
				route6 = true;
			}
		}
		if (route6) {
			rotZSkiperDer -= 0.2f;
			rotZSkiperIzq -= 0.2f;
			if (rotZSkiperDer < 30.0) {
				rotZKowalskiDer -= 0.2;
				rotZRicoIzq -= 0.2;
				if (rotYKowalskiDer > 0.0) {
					rotYRicoIzq += 0.2f;
					rotYKowalskiDer -= 0.2f;
					rotYSkiperDer -= 0.2f;
					rotYSkiperIzq += 0.2f;
				}
			}
			if (rotZSkiperDer < 0.0) {
				route6 = false;
				route1 = true;
				animPenguin = false;
			}
		}
	}
}

void animacionPanda() {
	if (animPanda) {
		if (part1) {
			if (pandaBicepDerRotX < 15.0f) {
				pandaBicepDerRotX += 0.09f;
				pandaBicepIzqRotX += 0.09f;
			}
			pandaAntebrazoDerRotY += 0.09f;
			pandaAntebrazoIzqRotY -= 0.09f;
			if (pandaAntebrazoIzqRotY < -90.0f) {
				part1 = false;
				part2 = true;
			}
		}
		if (part2) {
			if (pandaAntebrazoDerRotY > 20.0f)
				pandaAntebrazoDerRotY -= 0.09f;
			if (pandaBicepDerRotX > 0.0f)
				pandaBicepDerRotX -= 0.09f;
			if (pandaBicepDerRotZ < 45.0f)
				pandaBicepDerRotZ += 0.09f;
			if (pandaManoDerRotZ > -60.0)
				pandaManoDerRotZ -= 0.09f;
			pandaBicepDerRotY += 0.09;
			if (pandaBicepDerRotY > 100.0f) {
				part2 = false;
				part3 = true;
			}
		}
		if (part3) {
			if (pandaBicepDerRotZ > 0.0f)
				pandaBicepDerRotZ -= 0.09f;
			if (pandaManoDerRotZ < 0.0f)
				pandaManoDerRotZ += 0.09f;
			pandaBicepDerRotY -= 0.09f;
			if (pandaBicepDerRotY < 0.0f) {
				part3 = false;
				part4 = true;
			}
		}
		if (part4) {
			if (pandaAntebrazoIzqRotY < -20.0f)
				pandaAntebrazoIzqRotY += 0.09f;
			if (pandaBicepIzqRotX > 0.0f)
				pandaBicepIzqRotX -= 0.09f;
			if (pandaBicepIzqRotZ < 45.0f)
				pandaBicepIzqRotZ += 0.09f;
			if (pandaManoIzqRotZ < 60.0)
				pandaManoIzqRotZ += 0.09f;
			pandaBicepIzqRotY -= 0.09;
			if (pandaBicepIzqRotY < -100.0f) {
				part4 = false;
				part5 = true;
			}
		}
		if (part5) {
			if (pandaManoIzqRotZ > 0.0f)
				pandaManoIzqRotZ -= 0.09;
			if (pandaBicepIzqRotZ > 0.0f)
				pandaBicepIzqRotZ -= 0.09f;
			pandaBicepIzqRotY += 0.09f;
			if (pandaBicepIzqRotY > 0.0) {
				part5 = false;
				part6 = true;
			}
		}
		if (part6) {
			if (pandaBicepDerRotX < 15.0f) {
				pandaBicepDerRotX += 0.09f;
				pandaBicepIzqRotX += 0.09f;
			}
			if (pandaBicepDerRotZ > -5.0f) {
				pandaBicepIzqRotZ -= 0.09f;
				pandaBicepDerRotZ -= 0.09f;
			}
			pandaAntebrazoDerRotY += 0.09f;
			pandaAntebrazoIzqRotY -= 0.09f;
			if (pandaAntebrazoDerRotY > 90.0f) {
				part6 = false;
				part7 = true;
			}
		}
		if (part7) {
			if (pandaAntebrazoDerRotY > 0.0f)
				pandaAntebrazoDerRotY -= 0.15f;
			if (pandaBicepDerRotZ > -25.0f)
				pandaBicepDerRotZ -= 0.15f;
			pandaBicepDerRotX -= 0.15f;
			pandaManoDerRotX += 0.15f;
			if (pandaManoDerRotZ > -60.0f)
				pandaManoDerRotZ -= 0.15;
			if (pandaBicepDerRotX < -90.0f) {
				part7 = false;
				part8 = true;
			}
		}
		if (part8) {
			if (pandaAntebrazoDerRotY < 90.0f)
				pandaAntebrazoDerRotY += 0.15f;
			if (pandaBicepDerRotZ < 0.0f)
				pandaBicepDerRotZ += 0.15f;
			pandaBicepDerRotX += 0.15f;
			pandaManoDerRotX -= 0.15f;
			if (pandaManoDerRotZ < 0.0f)
				pandaManoDerRotZ += 0.15;

			if (pandaAntebrazoIzqRotY < 0.0f)
				pandaAntebrazoIzqRotY += 0.15f;
			if (pandaBicepIzqRotZ > -25.0f)
				pandaBicepIzqRotZ -= 0.15f;
			pandaBicepIzqRotX -= 0.15f;
			pandaManoIzqRotX += 0.15f;
			pandaAntebrazoDerRotY -= 0.15;
			if (pandaManoIzqRotZ < 60.0f)
				pandaManoIzqRotZ += 0.15;
			if (pandaBicepDerRotX > 0.0f) {
				part8 = false;
				part9 = true;
			}
		}
		if (part9) {
			if (pandaManoIzqRotZ > 0.0f)
				pandaManoIzqRotZ -= 0.15;
			if (pandaBicepIzqRotZ < 0.0f)
				pandaBicepIzqRotZ += 0.15f;
			pandaManoIzqRotX -= 0.15f;
			pandaBicepIzqRotX += 0.15f;
			if (pandaBicepIzqRotX > 0.0f) {
				part9 = false;
				part1 = true;
				animPanda = false;
			}
		}
	}
}
// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	//if (keys[GLFW_KEY_L])
	//{
	//	if (play == false && FrameIndex > 1)
	//	{

	//		resetElements();
	//		//First Interpolation				
	//		interpolation();

	//		play = true;
	//		playIndex = 0;
	//		i_curr_steps = 0;
	//	}
	//	else
	//	{
	//		play = false;
	//	}

	//}


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

	if (keys[GLFW_KEY_P])
		animPenguin = !animPenguin;

	if (keys[GLFW_KEY_O])
		animPanda = !animPanda;
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