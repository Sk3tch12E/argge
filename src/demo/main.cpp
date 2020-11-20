#include <argge/ARGGE.h>
#include <iostream>

int main()
{
	try
	{
		std::shared_ptr<Core> core = Core::initialize();

		std::shared_ptr<Entity> pe = core->addEntity();

		std::shared_ptr<Renderer> pc = pe->addComponent<Renderer>();



        //std::shared_ptr<Renderer> pm = pm->addComponent<Model>();


        /*#ifdef VERTEX
        attribute vec2 a_Position;  
        void main()
        {
            gl_Position = vec4(a_Position, 0, 1);
        }        
        #endif


        #ifdef FRAGMENT        
        void main()
        {
            gl_FragColor = vec4(1, 0, 0, 1);
        }
        #endif*/


		core->start();
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what()<<std::endl;
	}

	return 0;
}