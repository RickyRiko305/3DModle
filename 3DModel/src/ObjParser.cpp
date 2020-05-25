#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void ParseObj(vector < vector<float> > & vertice, vector < vector <unsigned int> > & indice )
{
	vector<float> vertices, textures, normals, index;
	vector<unsigned int> si[4];

	ifstream file;
	file.open("obj.txt", ifstream::in);
	string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line.find("object") != string::npos)
			{
				si[0].push_back(vertices.size());
				si[1].push_back(textures.size());
				si[2].push_back(normals.size());
				si[3].push_back(index.size());
			}
			while (line.substr(0, 2) == "vn")
			{
				stringstream s(line.substr(3)), ss1, ss2, ss3;
				float xf, yf, zf;
				getline(s, line, ' ');
				ss1 << line;
				ss1 >> xf;
				normals.push_back(xf);

				getline(s, line, ' ');
				ss2 << line;
				ss2 >> yf;
				normals.push_back(yf);

				getline(s, line, ' ');
				ss3 << line;
				ss3 >> zf;
				normals.push_back(zf);

				getline(file, line);
			}
			while (line.substr(0, 2) == "v ")
			{
				stringstream s(line.substr(3)), ss1, ss2, ss3;
				float xf, yf, zf;
				getline(s, line, ' ');
				ss1 << line;
				ss1 >> xf;
				vertices.push_back(xf);

				getline(s, line, ' ');
				ss2 << line;
				ss2 >> yf;
				vertices.push_back(yf);

				getline(s, line, ' ');
				ss3 << line;
				ss3 >> zf;
				vertices.push_back(zf);

				getline(file, line);
			}
			while (line.substr(0, 2) == "vt")
			{
				stringstream s(line.substr(3)), ss1, ss2, ss3;
				float xf, yf, zf;
				getline(s, line, ' ');
				ss1 << line;
				ss1 >> xf;
				textures.push_back(xf);

				getline(s, line, ' ');
				ss2 << line;
				ss2 >> yf;
				textures.push_back(yf);

				getline(s, line, ' ');
				ss3 << line;
				ss3 >> zf;
				textures.push_back(zf);

				getline(file, line);
			}
			while (line.substr(0, 2) == "f ")
			{

				istringstream s(line.substr(2));

				for (int i = 0; i < 3; i++)
				{
					getline(s, line, '/');
					index.push_back(stoul(line) - 1);

					getline(s, line, '/');
					if (si[0].size() < 4)
						index.push_back(stoul(line) - 1);

					getline(s, line, ' ');
					index.push_back(stoul(line) - 1);
				}
				getline(file, line);
			}
		}
	}
	else cout << "Error opening file\n";
	file.close();

	si[0].push_back(vertices.size());
	si[1].push_back(textures.size());
	si[2].push_back(normals.size());
	si[3].push_back(index.size());

	for (int x = 0; x < 4; x++)
	{
		for (int i = si[3][x]; i < si[3][x + 1]; )
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
					vertice[x].push_back(vertices[index[i] * 3 + k]);
				i++;

				if (x < 3)
				{
					for (int k = 0; k < 3; k++)
						vertice[x].push_back(textures[index[i] * 3 + k]);
					i++;
				}
				else
				{
					vertice[x].push_back(0.3f);
					vertice[x].push_back(0.8f);
					vertice[x].push_back(0.0f);
				}

				for (int k = 0; k < 3; k++)
					vertice[x].push_back(normals[index[i] * 3 + k]);
				i++;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = si[3][i], k = 0; j < si[3][i + 1] * 3; j++, k++)
			indice[i].push_back(k);
	}
}
