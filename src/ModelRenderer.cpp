#include "ModelRenderer.h"

static int fastrand(int g_seed) {
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}

#define OPT false

ModelRenderer::ModelRenderer(const char* path)
{

	Timer t("Model Rendering");
 
	const int vertexSize = 6;

	int numVerticies = 0, numIndicies = 0;
	int faceStart = 0, vertexStart = 0;
	
 
	std::filesystem::path p(path);
	std::pair<int, int> counts = ApproxVertexCount(std::filesystem::file_size(p));

	numVerticies = counts.first + 1;
	numIndicies = counts.second + 1;

	//malloc for easy realloc
	float* verticies = (float*)malloc(numVerticies * vertexSize * sizeof(float));
	uint32_t* indicies = (uint32_t*)malloc(numIndicies * sizeof(uint32_t));

	std::thread vertexThread([path, &verticies, vertexSize, &numVerticies]() mutable {

		FILE* file = fopen(path, "r");

		int actualVertexCount = 0;
		int currentSize = numVerticies;

		char line[64];
		int counter = 0;
		int total = 0;
		bool gettingVerticies = false;

		while (fgets(line, 64, file)) {

			if (gettingVerticies && (line[0] != 'v' || line[1] != ' ')) {
				break;
			}
			if (!gettingVerticies && line[0] == 'v' && line[1] == ' ') {
				gettingVerticies = true;
			}
			
			if (!gettingVerticies) continue;

			float first, second, third;
			int vals = sscanf(line, "v %f %f %f", &first, &second, &third);
			verticies[total] = first; verticies[total + 1] = second; verticies[total + 2] = third;
			verticies[total + 3] = (float)fastrand(counter) / (float)RAND_MAX; verticies[total + 4] = (float)fastrand(counter) / (float)RAND_MAX; verticies[total + 5] = (float)fastrand(counter) / (float)RAND_MAX;
			total += vertexSize;

			actualVertexCount++;

			if (actualVertexCount == currentSize) {
				float* temp = (float*)realloc(verticies, currentSize * vertexSize * 2 * sizeof(float));
				ASSERT(temp != NULL);
				verticies = temp;
				currentSize = currentSize * 2;
			}
			
			counter = fastrand(counter);
			//memset(line, 0, 64);
 

		}
		
		numVerticies = actualVertexCount;
		fclose(file);

	});


	std::thread faceThread([path, &indicies, &numIndicies]() mutable {
	 
		FILE* file = fopen(path, "r");

		int actualIndexCount = 0;

		char line[64];
		int total = 0;
		int currentSize = numIndicies;

		while (fgets(line, 64, file)) {

			if (line[0] == 'f' && line[1] == ' ') {
 
				int i[4] = { 0 };
				int vals = sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &i[0], &i[1], &i[2], &i[3]);
				int x = 1;
			 
				if (actualIndexCount + vals >= currentSize) {
					uint32_t* temp = (uint32_t*)realloc(indicies, currentSize * 2 * sizeof(uint32_t));
					ASSERT(temp != NULL);
					indicies = temp;
					currentSize = currentSize * 2;
				}
 
				if (vals == 3) {
					indicies[actualIndexCount] = (uint32_t)i[0] - 1; indicies[actualIndexCount + 1] = (uint32_t)i[1] - 1; indicies[actualIndexCount + 2] = (uint32_t)i[2] - 1;
					actualIndexCount += 3;
				}
				else if (vals == 4) {
					indicies[actualIndexCount] = (uint32_t)i[0] - 1; indicies[actualIndexCount + 1] = (uint32_t)i[1] - 1; indicies[actualIndexCount + 2] = (uint32_t)i[2] - 1;
					indicies[actualIndexCount + 3] = (uint32_t)i[0] - 1; indicies[actualIndexCount + 4] = (uint32_t)i[2] - 1; indicies[actualIndexCount + 5] = (uint32_t)i[3] - 1;
					actualIndexCount += 6;
				}
				else ASSERT(false);

			}

			//memset(line, 0, 64);
		}

		numIndicies = actualIndexCount;
		fclose(file);

	});


	vertexThread.join();
	faceThread.join();
	
	m_VertexBuffer = std::make_unique<VertexBuffer>(verticies, numVerticies * vertexSize * sizeof(float));
	m_IndexBuffer = std::make_unique<IndexBuffer>(indicies, numIndicies);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	m_VAO.AddBuffer(*m_VertexBuffer, layout);
	m_VAO.AddIndexBuffer(*m_IndexBuffer);
 
	free(verticies);
	free(indicies);
 
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::Render()
{
	m_VAO.Bind();
	glCall(glDrawElements(GL_TRIANGLES, m_VAO.GetCount(), GL_UNSIGNED_INT, nullptr));
}
