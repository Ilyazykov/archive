varying vec3 ModelPosition;   // ��������� ��������� � ��������� �����������

varying float LightIntensity;   // ������������� ����� �� ���������

uniform vec3 Spacing;   // ���������� ����� ��������

uniform float DotSize;   // ������ �������

uniform vec3 ModelColor;   // ���� �����������

uniform vec3 PolkaDotColor;   // ���� �������

void main(void)
{
   // ������� ��������� ��������� � ���������������� ������� ���������
   vec3 scaledPoint = ModelPosition - (Spacing * floor(ModelPosition / Spacing));

   // �������� �������� � ����� ���������������� ������� ���������
   scaledPoint -= Spacing / 2.0;

   // ������� ���������� �� ��������� � ���������������� ������� ���������
   float scaledPointLength = length(scaledPoint);
   
   // ���������� ���������� � �������� ������
   float insideSphere = step(scaledPointLength, DotSize);
   
   // ���������� ����������� ���� ���������
   vec3 finalColor = vec3(mix(ModelColor, PolkaDotColor, insideSphere));

   // �������� �������� � ���������� ���������
   gl_FragColor = vec4(finalColor * LightIntensity, 1.0);
}
