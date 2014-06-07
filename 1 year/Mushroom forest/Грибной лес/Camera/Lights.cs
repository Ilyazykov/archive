using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Tao.OpenGl;

namespace Грибной_лес
{
    class Light
    {
        float x;
        float y;
        float z;
        float l;
        bool flag;

        public Light()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            l = 0.0f;
            flag = true;
        }

        /// <summary> Настраивает источники света. </summary>
        public void SetupLights()
        {
            Gl.glEnable(Gl.GL_LIGHTING);
            Gl.glEnable(Gl.GL_LIGHT0);

            Gl.glLightfv(Gl.GL_LIGHT0, Gl.GL_AMBIENT, new float[] { 0.1f, 0.1f, 0.1f, 1.0f });
            Gl.glLightfv(Gl.GL_LIGHT0, Gl.GL_DIFFUSE, new float[] { 0.8f, 0.8f, 0.8f, 1.0f});
            Gl.glLightfv(Gl.GL_LIGHT0, Gl.GL_SPECULAR, new float[] { 0.9f, 0.9f, 0.9f, 1.0f });
        }

        public void MoveLight()
        {
            x = (float)(100.0 * Math.Cos((float)Form1.interation / 50));
            y = (float)(100.0 * Math.Sin((float)Form1.interation / 50));
            z = 0.0f;

            if (y > -70 && !flag)
            {
                Gl.glEnable(Gl.GL_LIGHT0);
                flag = !flag;
            }
            else if (y < -70 && flag)
            {
                Gl.glDisable(Gl.GL_LIGHT0);
                flag = !flag;
            }

            Gl.glLightfv(Gl.GL_LIGHT0, Gl.GL_POSITION, new float[] { x, y, z, l });
        }
    }
}
