using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Tao.OpenGl;
using Tao.DevIl;

namespace Грибной_лес
{
    public partial class Form1 : Form
    {
        #region Данные

        // Логика
        private int[,] field; // 7 - дерево, 5 и 6 - пустота

        private int X, Y; // размер поля (2 на края);

        public static int interation = 0; // номер интерации

        private bool pause = false; // нажата ли пауза

        //Графика
        double cadr = 15; // количество кадров для анимации роста грибов
        
        private Camera cam = new Camera();

        private Light light = new Light();

        private int myMouseXCoord = 0, myMouseYCoord = 0;

        private int myMouseXCoordVar = 0, myMouseYCoordVar = 0;

        private bool mouseRotate = false;

        private bool mouseMove = false;

        //туман
        int [] fogMode = { Gl.GL_EXP, Gl.GL_EXP2, Gl.GL_LINEAR }; // Хранит три типа тумана

        uint fogfilter= 3;                    // Тип используемого тумана

        float [] fogColor = {0.5f, 0.5f, 0.5f, 1.0f}; // Цвет тумана

        #endregion

        #region Запуск

        public Form1()
        {
            InitializeComponent();
            
            CreateField();

            AnT.InitializeContexts();

            InitGL();

            ResizeViewport(AnT.Width, AnT.Height);

            LoadShaders();
        }

        /// <summary>Создание поля при первом запуске</summary>
        private void CreateField() // первое условие
        {
            //---Подсчёт колва ячеек в поле------------------------------------

            StreamReader streamReader = new StreamReader("..\\..\\NewField.txt");

            X = Y = 0;

            while (streamReader.Read() != '\n')
            {
                X++;
            } X--; // подсчёт столбцов

            while (!streamReader.EndOfStream)
            {
                Y++;
                streamReader.ReadLine();
            } Y++; // подсчёт строк
            streamReader.Close();

            streamReader.Close();
            //-------------------------------------------------------------------

            //---Перенос данных из файла----------------------------------------
            field = new int[X + 2, Y + 2];
            streamReader = new StreamReader("..\\..\\NewField.txt");

            for (int y = 1; y <= Y; y++)
                for (int x = 1; x <= X; x++)
                {
                    int ololo = streamReader.Read();
                    if (ololo != 48 && ololo != 49)
                    {
                        streamReader.ReadLine();
                        ololo = streamReader.Read();
                    }
                    if (ololo == 48) field[x, y] = 6;
                    else if (ololo == 49) field[x, y] = 7;
                }
            //----------------------------------------------------------------------

            //---Заполнение боковых полей при первом запуске-----------------------
            for (int x = 0; x <= X + 1; x++)
            {
                field[x, 0] = field[x, Y];
                field[x, Y + 1] = field[x, 1];
            }
            for (int y = 0; y <= Y + 1; y++)
            {
                field[0, y] = field[X, y];
                field[X + 1, y] = field[1, y];
            }
            //----------------------------------------------------------------------
        }

        // изменение размеров окна
        private void AnT_Resize(object sender, EventArgs e)
        {
            ResizeViewport(AnT.Width, AnT.Height);
        }

        #endregion

        #region Матрицы

        /// <summary>Заполнение вспомогательных боковых полей</summary>
        private void CreateMask()
        {
            for (int x = 0; x <= X+1; x++)
            {
                if (field[x, 0] == 0 && field[x, Y] == 6) field[x, Y] = field[x, 0]; // появление маски
                if (field[x, Y + 1] == 0 && field[x, 1] == 6) field[x, 1] = field[x, Y + 1]; // появление маски
            }

            for (int y = 0; y <= Y+1; y++)
            {
                if (field[0, y] == 0 && field[X, y] == 6) field[X, y] = field[0, y]; // появление маски
                if (field[X + 1, y] == 0 && field[1, y] == 6) field[1, y] = field[X + 1, y]; // появление маски
            }

            if (field[1, 1] == 0) field[X + 1, 1] = field[X + 1, Y + 1] = field[1, Y + 1] = 0; // появление маски
            if (field[X, 1] == 0) field[0, 1] = field[0, Y + 1] = field[X, Y + 1] = 0; // появление маски
            if (field[X, Y] == 0) field[0, Y] = field[0, 0] = field[X, 0] = 0; // появление маски
            if (field[1, Y] == 0) field[1, 0] = field[X + 1, 0] = field[X + 1, Y] = 0; // появление маски
        }

        private void DestroyMask()
        {
            for (int x = 0; x <= X + 1; x++)
            {
                if (field[x, Y] == 5) field[x, 0] = 6; // уничтожение маски
                if (field[x, 1] == 5) field[x, Y + 1] = 6; // уничтожение маски
            }

            for (int y = 0; y <= Y + 1; y++)
            {
                if (field[X, y] == 5) field[0, y] = 6; // уничтожение маски
                if (field[1, y] == 5) field[X + 1, y] = 6; // уничтожение маски
            }

            if (field[1, 1] == 5) field[X + 1, 1] = field[X + 1, Y + 1] = field[1, Y + 1] = 6; // уничтожение маски
            if (field[X, 1] == 5) field[0, 1] = field[0, Y + 1] = field[X, Y + 1] = 6; // уничтожение маски
            if (field[X, Y] == 5) field[0, Y] = field[0, 0] = field[X, 0] = 6; // уничтожение маски
            if (field[1, Y] == 5) field[1, 0] = field[X + 1, 0] = field[X + 1, Y] = 6; // уничтожение маски
        }

        #endregion

        #region Интерации

        private void timer_Tick(object sender, EventArgs e)
        {
            if (!pause)
            {
                interation++;
                if (interation % cadr == 0)
                {
                    NextInteration();
                }   
            }
            else if (interation % cadr != cadr - 1)
            {
                interation++;
            }
            mouse_Events();
            light.MoveLight();
            cam.update();

            AnT.Invalidate();
        }

        /// <summary>Интерация</summary>
        private void NextInteration()
        {
   
            // Цикл для старения грибов
            for (int x = 1; x <= X; x++)
                for (int y = 1; y <= Y; y++)
                    if (field[x, y] < 6) field[x, y]++;

            // Поправление маски
            DestroyMask();

            Random rand = new Random();
            rand.Next();

            //Цикл для появления новых грибов
            for (int x = 1; x <= X; x++)
                for (int y = 1; y <= Y; y++)
                {
                    switch (field[x, y])
                    {
                        case 6: // пустое поле
                            break;
                        case 5: // исчезнувший гриб
                            break;
                        case 0: // только что появившиеся грибы не порождают новых грибов
                            break;

                        case 7: // дерево 
                            if (rand.Next(9) == 0) newMushroom(x, y); // 1/9 на появление гриба вокруг
                            break;
                        
                        default: // грибы разного возраста
                            if (rand.Next(9) % 3 == 0) newMushroom(x, y); // 1/3 на появление гриба вокруг
                            else if (rand.Next(9) % 3 == 1) // 1/3 на появление двух грибов вокруг
                            {
                                newMushroom(x, y);
                                newMushroom(x, y);
                            }
                            break;
                    }
                }

            // Поправление маски
            CreateMask();

            // Цикл для пометки 8й грибов у которых 3 и более соседей
            for (int x = 1; x <= X; x++)
                for (int y = 1; y <= Y; y++)
                    if (field[x, y] < 5) threeMashrooms(x, y);

            // Уничтожение грибов с пометкой 8
            for (int x = 1; x <= X; x++)
                for (int y = 1; y <= Y; y++)
                {
                    if (field[x, y] >= 8) field[x, y] -= 3;     
                }

            // Поправление маски
            DestroyMask();

        }

        private bool threeMashrooms(int x, int y)
        {
            int count = 0;

            for (int cell = 0; cell < 8; cell++)
            {
                Point point = SelectCell(cell, x, y);
                if (field[point.X, point.Y] < 5 || field[point.X, point.Y] >= 8) count++;

                if (count == 3)
                {
                    if (field[x, y] == 0) field[x, y] = 9;
                    else field[x, y] = 8;
                    return true;
                }
            }

            return false;
        }

        /// <summary>Выращиваем гриб, вблизи клетки</summary>
        private void newMushroom(int x, int y)
        {
            Random rand = new Random();

            int[] cell = new int[8] { -1, -1, -1, -1, -1, -1, -1, -1 };
            rand.Next();

            for (int i = -1; i < 8; i++)
            {
                int n = rand.Next(8);
                if (cell[n] == -1) cell[n] = i;
                else i--;
            }

            for (int i = 0; i < 8; i++)
            {
                Point point = SelectCell(cell[i], x, y);

                if (field[point.X, point.Y] == 6) // выбранное поле пустое?
                {
                    field[point.X, point.Y] = 0; // да - сажаем гриб
                    break;
                }
            }
        }

        /// <summary>
        /// Выбор ячейки по номеру
        /// </summary>
        /// <param name="cell">номер</param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        private Point SelectCell(int cell, int x, int y)
        {
            int x1 = 0, y1 = 0; // координаты новой ячейки
            switch (cell)
            {
                case 0:
                    x1 = x - 1; y1 = y - 1;
                    break;
                case 1:
                    x1 = x - 1; y1 = y;
                    break;
                case 2:
                    x1 = x - 1; y1 = y + 1;
                    break;
                case 3:
                    x1 = x; y1 = y - 1;
                    break;
                case 4:
                    x1 = x; y1 = y + 1;
                    break;
                case 5:
                    x1 = x + 1; y1 = y - 1;
                    break;
                case 6:
                    x1 = x + 1; y1 = y;
                    break;
                case 7:
                    x1 = x + 1; y1 = y + 1;
                    break;
            }

            return new Point(x1, y1);
        }

        #endregion

        #region Ручное управление

        private void openGlControl_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 32) pause = pause ? false : true; // пробел
            if (e.KeyChar == 'n' || e.KeyChar == 'N') NextInteration(); // N

            // управление камерой
            if (e.KeyChar == 'w' || e.KeyChar == 'W') cam.Move_Camera(0.1f); // Камеру вперёд
            if (e.KeyChar == 's' || e.KeyChar == 'S') cam.Move_Camera(-0.1f); // Камеру назад
            if (e.KeyChar == 'a' || e.KeyChar == 'A') cam.Strafe(-0.1f);  // Камеру влево
            if (e.KeyChar == 'd' || e.KeyChar == 'D') cam.Strafe(0.1f); // Камеру вправо

            if (cam.getPosY() < 10 && e.KeyChar == 'r' || e.KeyChar == 'R') cam.upDown(0.1f); // Камеру вверх
            if (cam.getPosY() > -0.4 && e.KeyChar == 'f' || e.KeyChar == 'F') cam.upDown(-0.1f); // Камеру вниз

            if (e.KeyChar == 'q' || e.KeyChar == 'Q') cam.Rotate_View(-0.1f); // Камеру повернуть влево
            if (e.KeyChar == 'e' || e.KeyChar == 'E') cam.Rotate_View(0.1f); // Камеру повернуть вправо


            if (e.KeyChar == 'z')
            {
                fogfilter += 1;
                if (fogfilter == 4) fogfilter = 0;
            }
        }

        private void openGlControl_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
                mouseRotate = true;

            if (e.Button == MouseButtons.Right)
                mouseMove = true;

            myMouseYCoord = e.X;
            myMouseXCoord = e.Y;
        }

        private void openGlControl_MouseUp(object sender, MouseEventArgs e)
        {
            mouseRotate = false;
            mouseMove = false;
        }

        private void openGlControl_MouseMove(object sender, MouseEventArgs e)
        {
            myMouseXCoordVar = e.Y;
            myMouseYCoordVar = e.X;
        }

        private void mouse_Events()
        {
            if (mouseRotate)
            {
                // меняем указатель
                AnT.Cursor = System.Windows.Forms.Cursors.SizeAll;

                //крутим
                cam.Rotate_Position((float)(myMouseYCoordVar - myMouseYCoord), 0.0f, 1.0f, 0.0f);

                // поднимаем и спускаем
                cam.upDown(((float)(myMouseXCoordVar - myMouseXCoord)) / 50);

                myMouseYCoord = myMouseYCoordVar;
                myMouseXCoord = myMouseXCoordVar;
            }
            else
            {
                if (mouseMove)
                {
                    AnT.Cursor = System.Windows.Forms.Cursors.SizeAll;

                    cam.Move_Camera((float)(myMouseXCoordVar - myMouseXCoord) / 50);
                    cam.Strafe(-((float)(myMouseYCoordVar - myMouseYCoord) / 50));

                    myMouseYCoord = myMouseYCoordVar;
                    myMouseXCoord = myMouseXCoordVar;

                }
                else
                {
                    AnT.Cursor = System.Windows.Forms.Cursors.Default;//возвращаем курсор
                };
            };
        }

        #endregion

        #region OpenGL

        private void openGlControl_Paint(object sender, PaintEventArgs e)
        {
            draw();
        }

        private void InitGL()
        {
            // инициализация библиотеки openIL
            Il.ilInit();
            Il.ilEnable(Il.IL_ORIGIN_SET);

            // загружаем текстуры
            loadImage();

            // включаем цвет и плавное затенение
            //Gl.glEnable(Gl.GL_COLOR_MATERIAL);
            Gl.glEnable(Gl.GL_TEXTURE_2D);      // Разрешить наложение текстуры
            Gl.glShadeModel(Gl.GL_SMOOTH);
     
            Gl.glClearDepth(1.0f);           // Установка буфера глубины
            Gl.glEnable(Gl.GL_DEPTH_TEST);  // включаем тест глубины
            Gl.glDepthFunc(Gl.GL_LEQUAL);       // Тип теста глубины

            // качественное вычисление перспективы
            Gl.glHint(Gl.GL_PERSPECTIVE_CORRECTION_HINT, Gl.GL_NICEST);

            // устанавливаем начальные позиции камеры
            cam.Position_Camera(0.0f, 0.0f, -4.0f, 
                1.0f, 0.0f, -4.0f, 
                0.0f, 1.0f, 0.0f);
            cam.update();

            light.SetupLights();// включаем освещение
        }

        private void ResizeViewport(int width, int height)
        {
            if (height == 0) height = 1;

            // устанавливаем размеры окна
            Gl.glViewport(0, 0, width, height);

            // задаём матрицу проекции
            Gl.glMatrixMode(Gl.GL_PROJECTION);
            Gl.glLoadIdentity();
            Glu.gluPerspective(45, width / (double)height, 0.1, 200);

            // сбрасываем модельную матрицу
            Gl.glMatrixMode(Gl.GL_MODELVIEW);
            Gl.glLoadIdentity();

        }

        #endregion

        #region Отрисовка

        private void draw()
        {
            // очищаем буфер цвета и глубины
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT);
            Gl.glClearColor(255, 255, 255, 1);

            if (fogfilter != 3) Fog();
            else Gl.glDisable(Gl.GL_FOG);
            
            // сбрасываем модельную матрицу
            Gl.glLoadIdentity();

            // положение камеры
            cam.Look();

            DrawField();
            DrawSky();

            for (int x = 1; x <= X; x++)
            {
                for (int y = 1; y <= Y; y++)
                {
                    Gl.glTranslated(0.0, 0.0, -2.1);
                    if (field[x, y] == 7) DrawTrees(); // рисуем дерево
                    else if (field[x, y] == 0) DrawMashrooms0(); // выращиваем новые грибы
                    else if (field[x, y] == 5) DrawMashrooms5(); // уничтожаем грибы
                    else if (field[x, y] < 5) DrawMashrooms(); // просто гриб
                }
                Gl.glTranslated(2.1, 0.0, Y * 2.1); // размер площадки [(X+1)*2.1] x [(Y+1)*2.1]
            }
        }

        private void Fog()
        {
            Gl.glEnable(Gl.GL_FOG);                       // Включает туман (GL_FOG)

            Gl.glFogi(Gl.GL_FOG_MODE, fogMode[fogfilter]);// Выбираем тип тумана

            Gl.glFogfv(Gl.GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана

            Gl.glFogf(Gl.GL_FOG_DENSITY, 0.25f);          // Насколько густым будет туман

            Gl.glHint(Gl.GL_FOG_HINT, Gl.GL_DONT_CARE);      // Вспомогательная установка тумана

            Gl.glFogf(Gl.GL_FOG_START, 1.0f);             // Глубина, с которой начинается туман

            Gl.glFogf(Gl.GL_FOG_END, 5.0f);               // Глубина, где туман заканчивается.
        }

        #region Элементы

        /// <summary>Нарисовать площадку</summary>
        private void DrawField()
        {
           
            // включаем режим текстурирования, указывая индификатор GrassTexture
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, GrassTexture);

            Gl.glBegin(Gl.GL_QUADS);
                
                Gl.glNormal3f(0.0f, 1.0f, 0.0f);
                Gl.glTexCoord2f(-30, -30);  Gl.glVertex3d(-100, -0.5, 100);
                Gl.glTexCoord2f(30, -30);   Gl.glVertex3d(100, -0.5, 100);
                Gl.glTexCoord2f(30, 30);    Gl.glVertex3d(100, -0.5, -100);
                Gl.glTexCoord2f(-30, 30);   Gl.glVertex3d(-100, -0.5, -100);

            Gl.glEnd();

        }

        /// <summary>Небо</summary>
        private void DrawSky()
        {
            Gl.glRotated(90, -1.0, 0.0, 0.0);

            // включаем режим текстурирования, указывая индификатор SkyTexture
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, SkyTexture);

            Glu.GLUquadric q = Glu.gluNewQuadric();
            Glu.gluQuadricTexture(q, Gl.GL_TRUE);
            Glu.gluQuadricDrawStyle(q, Glu.GLU_FILL);

            Glu.gluSphere(q, 100, 50, 50);
            Glu.gluDeleteQuadric(q);

            Gl.glRotated(90, 1.0, 0.0, 0.0);
        }
        
        /// <summary>Нарисовать дерево</summary>
        private void DrawTrees()
        {
            Glu.GLUquadric q = Glu.gluNewQuadric();
            Glu.gluQuadricTexture(q, Gl.GL_TRUE);
            Glu.gluQuadricDrawStyle(q, Glu.GLU_FILL);

            Gl.glTranslated(0.0, -0.5, 0.0);
            Gl.glRotated(90, -1.0, 0.0, 0.0);

            { // рисуем ствол
                // включаем режим текстурирования, указывая индификатор WoodTexture
                Gl.glBindTexture(Gl.GL_TEXTURE_2D, WoodTexture);

                // рисуем цилиндр
                Glu.gluCylinder(q, 0.2, 0.2, 2, 50, 50);

            }

            { // рисуем крону

                // включаем режим текстурирования, указывая индификатор TreeTexture
                Gl.glBindTexture(Gl.GL_TEXTURE_2D, TreeTexture);

                // рисуем сферу
                Gl.glTranslated(0.0, 0.0, 2.0);
                
                Glu.gluSphere(q, 1, 50, 50);
                Gl.glTranslated(0.0, 0.0, -2.0);
            }

            Gl.glRotated(90, 1.0, 0.0, 0.0);
            Gl.glTranslated(0.0, 0.5, 0.0);

            Glu.gluDeleteQuadric(q);
        }

        #region Виды грибов

        /// <summary>Нарисовать Гриб</summary>
        private void DrawMashrooms()
        {
            Glu.GLUquadric q = Glu.gluNewQuadric();
            Glu.gluQuadricTexture(q, Gl.GL_TRUE);
            Glu.gluQuadricDrawStyle(q, Glu.GLU_FILL);

            Gl.glTranslated(0.0, -0.2, 0.0);
            Gl.glRotated(90, 1.0, 0.0, 0.0);

            { //рисуем ножку

                // включаем режим текстурирования, указывая индификатор SkyTexture
                Gl.glBindTexture(Gl.GL_TEXTURE_2D, MashroomTexture);

                // рисуем цилиндр
                Glu.gluCylinder(q, 0.1, 0.1, 0.3, 50, 50);

                Gl.glTranslated(0.0, 0.0, -0.3);
            }

            // Настраиваем и используем шейдер
            //useShaderForMashrooms();

            // включаем режим текстурирования, указывая индификатор TreeTexture
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, MashroomHatTexture);

            // рисуем шляпу
            Glu.gluCylinder(q, 0.0, 0.5, 0.3, 50, 50);

            // отключаем шейдер
            //Gl.glUseProgram(0);

            Gl.glTranslated(0.0, 0.0, 0.3);

            Gl.glRotated(90, -1.0, 0.0, 0.0);
            Gl.glTranslated(0.0, 0.2, 0.0);

            Glu.gluDeleteQuadric(q);
        }

        /// <summary>для новых грибов</summary>
        private void DrawMashrooms0()
        {

            double mash = (double)(interation % cadr + 1) / cadr;
            double lol = (double)(1 - mash) / 2.0;
            Gl.glTranslated(0.0, -lol, 0.0);
            Gl.glScaled(mash, mash, mash);

            DrawMashrooms();

            mash = 1.0 / mash;
            Gl.glScaled(mash, mash, mash);
            Gl.glTranslated(0.0, lol, 0.0);
        }

        /// <summary>для умирающих грибов</summary>
        private void DrawMashrooms5()
        {
            double mash = (double)(cadr - interation % cadr) / cadr;
            double lol = (double)(1 - mash) / 2.0;
            Gl.glTranslated(0.0, -lol, 0.0);
            Gl.glScaled(mash, mash, mash);

            DrawMashrooms();

            mash = 1.0 / mash;
            Gl.glScaled(mash, mash, mash);
            Gl.glTranslated(0.0, lol, 0.0);
        }

        #endregion

        #endregion

        #endregion

        #region Шейдеры

        private int vertex = 0;

        private int fragment = 0;

        private int programMashrooms = 0;

        void LoadShaders()
        {
            //vertex = Gl.glCreateShader(Gl.GL_VERTEX_SHADER);
            //fragment = Gl.glCreateShader(Gl.GL_FRAGMENT_SHADER);

            //StreamReader sr = new StreamReader("..//..//shaders//RenderShader.vs");
            //Gl.glShaderSource(vertex, 1, new string[] { sr.ReadToEnd() }, null);
            //sr.Close();

            //sr = new StreamReader("..//..//shaders//RenderShader.fs");
            //Gl.glShaderSource(fragment, 1, new string[] { sr.ReadToEnd() }, null);
            //sr.Close();

            //Gl.glCompileShader(vertex);
            //Gl.glCompileShader(fragment);

            //programMashrooms = Gl.glCreateProgram();

            //Gl.glAttachShader(programMashrooms, vertex);
            //Gl.glAttachShader(programMashrooms, fragment);

            //Gl.glLinkProgram(programMashrooms);

            //sr = null;
            //GC.Collect();
        }

        private void useShaderForMashrooms()
        {
            {
                Gl.glUseProgram(programMashrooms);

                int location = Gl.glGetUniformLocation(programMashrooms, "LightPosition");
                Gl.glUniform3fv(location, 1, new float[] { 10f, 10f, 10f });

                // Устанавливаем цвет кружков
                Color dotColor = Color.White;
                location = Gl.glGetUniformLocation(programMashrooms, "PolkaDotColor");
                Gl.glUniform3fv(location, 1, new float[] { dotColor.R / 255f, dotColor.G / 255f, dotColor.B / 255f });

                // Устанавливаем цвет модели
                Color modelColor = Color.Red;
                location = Gl.glGetUniformLocation(programMashrooms, "ModelColor");
                Gl.glUniform3fv(location, 1, new float[] { modelColor.R / 255f, modelColor.G / 255f, modelColor.B / 255f });

                // Устанавливаем расстояние между кружками
                float spacing = 0.15f;
                location = Gl.glGetUniformLocation(programMashrooms, "Spacing");
                Gl.glUniform3fv(location, 1, new float[] { spacing, spacing, spacing });

                // Устанавливаем размер кружков
                location = Gl.glGetUniformLocation(programMashrooms, "DotSize");
                Gl.glUniform1f(location, 0.05f);

            }
        }

        #endregion

        #region Текстуры

        // индефекатор текстуры
        public int imageId = 0;

        // текстурные объекты
        public uint GrassTexture = 0; // трава
        public uint SkyTexture = 0; // небо
        public uint TreeTexture = 0; // крона дерева
        public uint WoodTexture = 0; // нога дерева
        public uint MashroomTexture = 0; // нога гриба
        public uint MashroomHatTexture = 0; //шляпа гриба

        void loadImage()
        {
            TextureLoad("..\\..\\Textures\\grass.png", ref GrassTexture);
            TextureLoad("..\\..\\Textures\\sky.png", ref SkyTexture);
            TextureLoad("..\\..\\Textures\\tree_hat.bmp", ref TreeTexture);
            TextureLoad("..\\..\\Textures\\wood2.png", ref WoodTexture);
            TextureLoad("..\\..\\Textures\\wood.png", ref MashroomTexture);
            TextureLoad("..\\..\\Textures\\mushroom_hat.bmp", ref MashroomHatTexture);
        }

        void TextureLoad(string url, ref uint texture)
        {
            // создаём изображение с идентификатором imageId
            Il.ilGenImages(1, out imageId);
            // делаем изображение текущим
            Il.ilBindImage(imageId);

            // пробуем загрузить изображение
            if (Il.ilLoadImage(url))
            {
                // Convert To An Easy-To-Use Format/Type
                Il.ilConvertImage(Il.IL_BGR, Il.IL_UNSIGNED_BYTE);

                Gl.glGenTextures(1, out texture);

                // Create MipMapped Texture
                Gl.glBindTexture(Gl.GL_TEXTURE_2D, texture);
                Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MAG_FILTER, Gl.GL_LINEAR);
                Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MIN_FILTER, Gl.GL_LINEAR_MIPMAP_NEAREST);
                Glu.gluBuild2DMipmaps(Gl.GL_TEXTURE_2D, Il.ilGetInteger(Il.IL_IMAGE_BPP), Il.ilGetInteger(Il.IL_IMAGE_WIDTH),
                                Il.ilGetInteger(Il.IL_IMAGE_HEIGHT), Il.IL_BGR, Il.ilGetInteger(Il.IL_IMAGE_TYPE), Il.ilGetData());

                Il.ilDeleteImages(1, ref imageId);
            }
        }

        #endregion
    }
}