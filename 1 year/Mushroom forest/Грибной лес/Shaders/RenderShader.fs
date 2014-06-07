varying vec3 ModelPosition;   // Положение фрагмента в модельных координатах

varying float LightIntensity;   // Интенсивность света во фрагменте

uniform vec3 Spacing;   // Расстояние между кружками

uniform float DotSize;   // Размер кружков

uniform vec3 ModelColor;   // Цвет поверхности

uniform vec3 PolkaDotColor;   // Цвет кружков

void main(void)
{
   // Находим положение фрагмента в масштабированной системе координат
   vec3 scaledPoint = ModelPosition - (Spacing * floor(ModelPosition / Spacing));

   // Помещаем фрагмент в центр масштабированной системы координат
   scaledPoint -= Spacing / 2.0;

   // Находим расстояние до фрагмента в масштабированной системы координат
   float scaledPointLength = length(scaledPoint);
   
   // Сравниваем расстоняие с радиусом кружка
   float insideSphere = step(scaledPointLength, DotSize);
   
   // Определяем собственный цвет фрагмента
   vec3 finalColor = vec3(mix(ModelColor, PolkaDotColor, insideSphere));

   // Затеняем фрагмент и возвращаем результат
   gl_FragColor = vec4(finalColor * LightIntensity, 1.0);
}
