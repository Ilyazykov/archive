using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Tao.OpenGl;

namespace Грибной_лес
{
    class Camera
    {
        #region private

        private struct Vector3D
        {
            public float x, y, z;
        };

        private Vector3D mPos; // вектор позиции камеры
        private Vector3D mView; // куда смотрит камера
        private Vector3D mUp; // Вектор верхнего направления
        private Vector3D mStrafe; // Вектор для стрейфа (движения влево и вправо)

        /// <summary>Нахождение перпендикулярного вектора</summary>
        /// <param name="vV1">координаты 1й точки</param>
        /// <param name="vV2">координаты 2й точки</param>
        /// <param name="vVector2">координаты 2го вектора</param>
        /// <returns>Перпендикуляр</returns>
        private Vector3D Cross(Vector3D vV1, Vector3D vV2, Vector3D vVector2)
        {
            Vector3D vNormal;
            Vector3D vVector1;
            vVector1.x = vV1.x - vV2.x;
            vVector1.y = vV1.y - vV2.y;
            vVector1.z = vV1.z - vV2.z;

            vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
            vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
            vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

            return vNormal;
        }

        /// <summary>Возвращает длину вектора</summary>
        private float Magnitude(Vector3D vNormal)
        {
            return (float)Math.Sqrt((vNormal.x * vNormal.x) +
                (vNormal.y * vNormal.y) +
                (vNormal.z * vNormal.z));
        }

        /// <summary>Возвращает вектор с длиной 1</summary>
        private Vector3D Normalize(Vector3D vVector)
        {
            // Вычислим величину вектора
            float magnitude = Magnitude(vVector);

            // Разделим все координаты на величину - получим длину 1
            vVector.x = vVector.x / magnitude;
            vVector.y = vVector.y / magnitude;
            vVector.z = vVector.z / magnitude;

            return vVector;
        }

        #endregion

        #region public

        public void Position_Camera(float pos_x, float pos_y, float pos_z,
            float view_x, float view_y, float view_z,
            float up_x, float up_y, float up_z)
        {
            mPos.x = pos_x;     //Позиция камеры
            mPos.y = pos_y;     //
            mPos.z = pos_z;     //
            mView.x = view_x;   //Куда смотрит, т.е. взгляд
            mView.y = view_y;   //
            mView.z = view_z;   //
            mUp.x = up_x;       //Вертикальный вектор камеры
            mUp.y = up_y;       //
            mUp.z = up_z;       //
        }

        /// <summary>Кучение камеры вокруг оси</summary>
        /// <param name="speed">сила поворота</param>
        public void Rotate_View(float speed)
        {
            Vector3D vVector; // Получим вектор взгляда
            vVector.x = mView.x - mPos.x;
            vVector.y = mView.y - mPos.y;
            vVector.z = mView.z - mPos.z;

            mView.z = (float)(mPos.z + Math.Sin(speed) * vVector.x + Math.Cos(speed) * vVector.z);
            mView.x = (float)(mPos.x + Math.Cos(speed) * vVector.x - Math.Sin(speed) * vVector.z);
        }

        public void Rotate_Position(float angle, float x, float y, float z)
        {
            mPos.x = mPos.x - mView.x;
            mPos.y = mPos.y - mView.y;
            mPos.z = mPos.z - mView.z;

            Vector3D vVector = mPos;
            Vector3D AVector;

            float SinA = (float)Math.Sin(Math.PI * angle / 180.0);
            float CosA = (float)Math.Cos(Math.PI * angle / 180.0);

            // Найдем новую позицию X для вращаемой точки 
            AVector.x = (CosA + (1 - CosA) * x * x) * vVector.x;
            AVector.x += ((1 - CosA) * x * y - z * SinA) * vVector.y;
            AVector.x += ((1 - CosA) * x * z + y * SinA) * vVector.z;

            // Найдем позицию Y 
            AVector.y = ((1 - CosA) * x * y + z * SinA) * vVector.x;
            AVector.y += (CosA + (1 - CosA) * y * y) * vVector.y;
            AVector.y += ((1 - CosA) * y * z - x * SinA) * vVector.z;

            // И позицию Z 
            AVector.z = ((1 - CosA) * x * z - y * SinA) * vVector.x;
            AVector.z += ((1 - CosA) * y * z + x * SinA) * vVector.y;
            AVector.z += (CosA + (1 - CosA) * z * z) * vVector.z;

            mPos.x = mView.x + AVector.x;
            mPos.y = mView.y + AVector.y;
            mPos.z = mView.z + AVector.z;
        }

        /// <summary>Перемещение камеры</summary>
        /// <param name="speed">скорость</param>
        public void Move_Camera(float speed)
        {
            Vector3D vVector; // получаем вектор взгляда
            vVector.x = mView.x - mPos.x;
            vVector.y = mView.y - mPos.y;
            vVector.z = mView.z - mPos.z;

            vVector.y = 0.0f; // Запрещает камере подниматься вверх
            vVector = Normalize(vVector);

            mPos.x += vVector.x * speed;
            mPos.z += vVector.z * speed;
            mView.x += vVector.x * speed;
            mView.z += vVector.z * speed;
        }

        /// <summary>Стрейф</summary>
        public void Strafe(float speed)
        {
            // Добавим вектор стрейфа к позиции
            mPos.x += mStrafe.x * speed;
            mPos.z += mStrafe.z * speed;

            // Добавим к взгляду
            mView.x += mStrafe.x * speed;
            mView.z += mStrafe.z * speed;
        }

        /// <summary>Для стрейфа в каждый момент времени нужно вычислять перпендикуляр</summary>
        public void update()
        {
            Vector3D vCross = Cross(mView, mPos, mUp);

            //Нормализуем вектор стрейфа
            mStrafe = Normalize(vCross);
        }

        /// <summary>Поворот камеры вверх и вниз</summary>
        public void upDown(float speed)
        {
            mPos.y += speed;
        }

        public void Look()
        {
            Glu.gluLookAt(mPos.x, mPos.y, mPos.z,
              mView.x, mView.y, mView.z,
              mUp.x, mUp.y, mUp.z);
        }

        public double getPosY() //Возвращает позицию камеры по Y
        {
            return mPos.y;
        }

        #endregion
    }
}
