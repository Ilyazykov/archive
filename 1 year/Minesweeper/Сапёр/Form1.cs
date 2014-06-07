using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Supper
{
    public partial class Form1 : Form
    {
        #region Переменные

        byte[,] field; // поле
                       // 7 - мина, 0..6 - количество мин вокруг

        byte[,] mask; // открытые и закрытые поля
                      // 0 - открыто, 1 - закрыто, 2 - флажок, 3 - граница

        int X = 10, Y = 10; //размер поля

        int mines = 20; // количество мин

        int size = 20; // размер шестигранников

        Point indent = new Point(50, 50); // отступ от края

        Font font = new Font("Arial", 20);

        StringFormat stringFormat = new StringFormat();

        bool newGame = true; // начата ли новая игра?

        byte WinOrFail = 0; // выигрыш или поражение
                            // 1 - выигрыш, 2 - поражение, 0 - игра

        int Ostalos; // Осталось открыть полей

        //нужные тригонометрические равенства
        double cos60 = Math.Cos(Math.PI / 3);
        double sin60 = Math.Sin(Math.PI / 3);
        double ctg60 = Math.Tan(Math.PI / 6);
        double cosec60 = 1 / Math.Sin(Math.PI / 3);

        #endregion

        #region Матрицы

        /// <summary>Создание пустого поля</summary>
        private void InitializeField()
        {
            field = new byte[X + 2, Y + 2];
            int x, y;
            for (x = 0; x < X+2; x++)
                for (y = 0; y < Y+2; y++)
                    field[x, y] = 0;

            mask = new byte[X + 2, Y + 2];
            for (x = 1; x < X + 1; x++)
                for (y = 0; y < Y + 2; y++)
                    mask[x, y] = 1; //скрытое поле

            for (x = 0; x < X + 2; x++)
            {
                mask[x, 0] = 3; // границы
                mask[x, Y + 1] = 3; // границы
            }

            for (y = 1; y < Y + 1; y++)
            {
                mask[0, y] = 3; // границы
                mask[X + 1, y] = 3; // границы
            }
        }

        /// <summary>Заполнение поля при создании новой игры</summary>
        /// <param name="pushX">нажатая ячайка (по X)</param><param name="y">нажатая ячайка (по Y)</param>
        private void CreateField(int pushX, int pushY)
        {
            InitializeField();

            //Размещение мин
            Random rand = new Random();
            for (int i = 0; i < mines; i++)
            {
                int x = rand.Next(X)+1;
                int y = rand.Next(Y)+1;
                if (field[x, y] != 7 && pushX != x && pushY != y) field[x, y] = 7; // 7 - это мина
                else i--;
            }

            //Заполнение цифрами
            for (int x = 1; x < X+1; x++)
                for (int y = 1; y < Y+1; y++)
                {
                    if (field[x, y] != 7)
                    {
                        if (field[x - 1, y] == 7) field[x, y]++;
                        if (field[x - 1, y + 1] == 7) field[x, y]++;
                        if (field[x, y - 1] == 7) field[x, y]++;
                        if (field[x, y + 1] == 7) field[x, y]++;
                        if (field[x + 1, y - 1] == 7) field[x, y]++;
                        if (field[x + 1, y] == 7) field[x, y]++;
                    }
                }

            Invalidate();
        }

        // открытие поля
        private void openField(int x, int y)
        {
            if (field[x, y] == 0 && mask[x, y] == 1)
            {
                mask[x, y] = 0;
                Ostalos--;

                openField(x + 1, y);
                openField(x + 1, y - 1);
                openField(x, y - 1);
                openField(x, y + 1);
                openField(x - 1, y);
                openField(x - 1, y + 1);
            }
            else if (mask[x, y] == 1)
            {
                mask[x, y] = 0;
                Ostalos--;
            }

            if (mask[x, y] == 0 && field[x, y] == 7) Fail();
            else if (Ostalos == 0) WinOrFail = 1;
        }

        private void flagField(int x, int y)
        {
            if (mask[x, y] == 1) mask[x, y] = 2;
            else if (mask[x, y] == 2) mask[x, y] = 1;
        }

        #endregion

        #region Преобразования

        /// <summary>Преобразование из ячейки матрицы в точку на плоскости</summary>
        /// <param name="x">координаты по x</param><param name="y">координаты по y</param>
        /// <returns>Точка на стандартной плоскости</returns>
        Point transformation(int x, int y)
        {
            int newX, newY;
            newX = (int)((x + y * cos60) * size * 2) + indent.X;
            newY = (int)(y * sin60 * size * 2) + indent.Y;
            Point newPoint = new Point(newX, newY);
            return newPoint;
        }

        /// <summary>Вычисление координат в матрице по заданию точки на плоскости</summary>
        /// <param name="x">координаты по x</param><param name="y">координаты по y</param>
        /// <returns>Координаты в матрице</returns>
        Point transformationInverse(int x, int y)
        {
            Point ololo = transformation(1, 1);
            int min = (x - ololo.X) * (x - ololo.X) + (y - ololo.Y) * (y - ololo.Y);
            int minX = 1;
            int minY = 1;
            int r;

            for (int x1 = 0; x1 < X + 2; x1++)
                for (int y1 = 0; y1 < Y + 2; y1++)
                {
                    ololo = transformation(x1, y1);
                    r = (x - ololo.X) * (x - ololo.X) + (y - ololo.Y) * (y - ololo.Y);
                    if (r < min)
                    {
                        min = r;
                        minX = x1;
                        minY = y1;
                    }
                }
            Point newPoint = new Point(minX, minY);
            return newPoint;
        } //Не очень эффективная вроде

        #endregion

        #region Отображение на экран

        //Отрисовка игрового поля
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics graphics = e.Graphics;

            // включаем сглаживание линий
            graphics.SmoothingMode = SmoothingMode.HighQuality;

//-----Отрисовка поля основная-----------------------------------------------------------

            for (int x = 1; x < X + 1; x++)
                for (int y = 1; y < Y + 1; y++)
                {
                    // Находим центр текущего шестиугольника
                    Point center = transformation(x, y);


                    Point[] points = new Point[] { new Point(center.X, (int)(center.Y - size * cosec60)),
					                             new Point((int)(center.X + size), (int)(center.Y - size * ctg60)),
					                             new Point((int)(center.X + size), (int)(center.Y + size * ctg60)),
					                             new Point(center.X, (int)(center.Y + size * cosec60)),
                                                 new Point((int)(center.X - size), (int)(center.Y + size * ctg60)),
                                                 new Point((int)(center.X - size), (int)(center.Y - size * ctg60))};

                    if (mask[x, y] == 0)
                    {
                        using (Brush backgraund = new SolidBrush(Color.DarkGray))
                        {
                            graphics.FillPolygon(backgraund, points);
                        }
                        switch (field[x, y])
                        {
                            case 1:
                                using (Brush brush = new SolidBrush(Color.Blue))
                                { graphics.DrawString("1", font, brush, center, stringFormat); }
                                break;
                            case 2:
                                using (Brush brush = new SolidBrush(Color.Green))
                                { graphics.DrawString("2", font, brush, center, stringFormat); }
                                break;
                            case 3:
                                using (Brush brush = new SolidBrush(Color.Red))
                                { graphics.DrawString("3", font, brush, center, stringFormat); }
                                break;
                            case 4:
                                using (Brush brush = new SolidBrush(Color.FromArgb(0, 0, 127)))
                                { graphics.DrawString("4", font, brush, center, stringFormat); }
                                break;
                            case 5:
                                using (Brush brush = new SolidBrush(Color.FromArgb(0, 63, 0)))
                                { graphics.DrawString("5", font, brush, center, stringFormat); }
                                break;
                            case 6:
                                using (Brush brush = new SolidBrush(Color.FromArgb(127, 0, 0)))
                                { graphics.DrawString("6", font, brush, center, stringFormat); }
                                break;
                            case 7:
                                using (Brush brush = new SolidBrush(Color.Red))
                                { graphics.FillPolygon(brush, points); }
                                break;
                        }
                    }
                    else if (mask[x, y] == 2)
                        using (Brush backgraund = new SolidBrush(Color.Orange))
                        {
                            graphics.FillPolygon(backgraund, points);
                        }
                    else
                        using (Brush backgraund = new SolidBrush(Color.Gray))
                        {
                            graphics.FillPolygon(backgraund, points);
                        }

                    using (Pen pen = new Pen(Color.White))
                    {
                        graphics.DrawPolygon(pen, points);
                    }
                }

//---------------------------------------------------------------------------------------

            if (WinOrFail == 1) // событие выигрыша
                using (Brush brush = new SolidBrush(Color.Green))
                { graphics.DrawString("Выиграл!!!", font, brush, 10, 25); }
            else if (WinOrFail == 2) // событие поражения
                using (Brush brush = new SolidBrush(Color.Red))
                { graphics.DrawString("Проиграл!!!", font, brush, 10, 25); }
        }

        #endregion

        #region Мышь

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left && WinOrFail == 0)
            {
                Point coorde = transformationInverse(e.X, e.Y);
                if (newGame)
                {
                    newGame = false;
                    CreateField(coorde.X, coorde.Y);
                }
                openField(coorde.X, coorde.Y);
            }
            
            if (e.Button == MouseButtons.Right && WinOrFail == 0)
            {
                Point coorde = transformationInverse(e.X, e.Y);
                flagField(coorde.X, coorde.Y);
            }

            Invalidate();
        }

        #endregion

        #region Победа и поражение
        
        // Проигрыш
        private void Fail()
        {
            WinOrFail = 2;

            for (int x = 1; x < X + 1; x++)
                for (int y = 1; y < Y + 1; y++)
                {
                    if (field[x, y] == 7) mask[x, y] = 0;
                }
        }

        #endregion

        #region Разное

        //Создание формы
        public Form1()
        {
            InitializeComponent();
            InitializeField();

            // устанавливаем параметры рисования надписей (выравнивание по центру)
            stringFormat.Alignment = StringAlignment.Center;
            stringFormat.LineAlignment = StringAlignment.Center;
        }

        // Нажатие клавиши Новая игра
        private void новаяИграToolStripMenuItem_Click(object sender, EventArgs e)
        {
            InitializeField();
            newGame = true;
            WinOrFail = 0;
            Ostalos = X * Y - mines;
            Invalidate();
        }

        // Клавиша выхода
        private void выходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        #endregion

        #region Недоделанная часть

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            //coorve = transformationInverse(e.X, e.Y);
            //Point.MessageBox.Show(coorve.X + " " + coorve.Y);
        }

        //Point coorve;
        // Клавиша мыши отпущена

        #endregion
    }
}