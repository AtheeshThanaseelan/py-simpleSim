#include "region.h"
#include <iostream>

region::region(std::array<std::array<int, 2>, 4> vertices):m_vertices{ vertices }
{
	//Represent and check a 2D defined region
	//Define verticies
	//Run a line through X, then Y. See if line intersects with lines definded in verticies

	


}

void region::draw(graphics_interface* gfxprovider)
{
	for (int i = 0; i < 4; i++)
	{
		std::array<float, 6> line;
		line[0] = m_vertices[i][0];
		line[1] = 1;
		line[2] = m_vertices[i][1];

		if (i == 3)
		{
			line[3] = m_vertices[0][0];
			line[4] = 1;
			line[5] = m_vertices[0][1];
		}
		else
		{
			line[3] = m_vertices[i+1][0];
			line[4] = 1;
			line[5] = m_vertices[i+1][1];
		}
		gfxprovider->add_line(line);
	}
}

void region::check(std::array <int, 2> point)
{
	//Ray Cross Method
	int ray_crosses = 0;
	std::array <float, 3> size{ 0.1, 0.1,0.1 };
	std::array <float, 3> pos{ 2,1,2 };

	for (int i = 0; i < 4; i++)
	{
		std::array <bool, 2> point_exist;
		for (int j = 0; j < 2; j++)
		{
			if (i == 3)
			{
				if (m_vertices[i][j] > point[j])
				{
					if (m_vertices[0][j] < point[j])
					{
						point_exist[j] = true;
					}
				}
				if (m_vertices[i][j] < point[j])
				{
					if (m_vertices[0][j] > point[j])
					{
						point_exist[j] = true;
					}
				}
			}
			else if (m_vertices[i][j] > point[j])
			{
				if (m_vertices[i + 1][j] < point[j])
				{
					point_exist[j] = true;
				}
			}
			else if (m_vertices[i][j] < point[j])
			{
				if (m_vertices[i + 1][j] > point[j])
				{
					point_exist[j] = true;
				}
			}

			if (point_exist[0] == true && point_exist[1] == true)
			{
				ray_crosses++;
			}

		}
	}

	std::cout << ray_crosses << std::endl;
}