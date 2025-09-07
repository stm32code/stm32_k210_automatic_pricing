#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"
#include "delay.h"
#include "string.h"

u8 OLED_GRAM[144][8];

// ���Ժ���
void OLED_ColorTurn(u8 i)
{
	if (i == 0)
	{
		OLED_WR_Byte(0xA6, OLED_CMD); // ������ʾ
	}
	if (i == 1)
	{
		OLED_WR_Byte(0xA7, OLED_CMD); // ��ɫ��ʾ
	}
}

// ��Ļ��ת180��
void OLED_DisplayTurn(u8 i)
{
	if (i == 0)
	{
		OLED_WR_Byte(0xC8, OLED_CMD); // ������ʾ
		OLED_WR_Byte(0xA1, OLED_CMD);
	}
	if (i == 1)
	{
		OLED_WR_Byte(0xC0, OLED_CMD); // ��ת��ʾ
		OLED_WR_Byte(0xA0, OLED_CMD);
	}
}
// дָ��
// DATA д����
// CMD дָ��
void OLED_WR_Byte(u8 dat, u8 cmd)
{
	u8 i;
	if (cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();
	OLED_CS_Clr();
	for (i = 0; i < 8; i++)
	{
		OLED_SCLK_Clr();
		if (dat & 0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat <<= 1;
	}
	OLED_CS_Set();
	OLED_DC_Set();
}

// ����OLED��ʾ
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D, OLED_CMD); // ��ɱ�ʹ��
	OLED_WR_Byte(0x14, OLED_CMD); // ������ɱ�
	OLED_WR_Byte(0xAF, OLED_CMD); // ������Ļ
}

// �ر�OLED��ʾ
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D, OLED_CMD); // ��ɱ�ʹ��
	OLED_WR_Byte(0x10, OLED_CMD); // �رյ�ɱ�
	OLED_WR_Byte(0xAF, OLED_CMD); // �ر���Ļ
}

// OLEDȫ�����
void OLED_Fill(u8 fill_Data)
{
	u8 m, n;
	for (m = 0; m < 8; m++)
	{
		OLED_WR_Byte(0xb0 + m, OLED_CMD); // page0-page1
		OLED_WR_Byte(0x00, OLED_CMD);	  // low column start address
		OLED_WR_Byte(0x10, OLED_CMD);	  // high column start address
		for (n = 0; n < 130; n++)
		{
			OLED_WR_Byte(fill_Data, OLED_DATA);
		}
	}
}
// ��������
void OLED_Clear(void)
{
	OLED_Fill(0x00);
}

// ����
// x:0~127
// y:0~63
void OLED_DrawPoint(u8 x, u8 y)
{
	u8 i, m, n;
	i = y / 8;
	m = y % 8;
	n = 1 << m;
	OLED_GRAM[x][i] |= n;
}

// ���һ����
// x:0~127
// y:0~63
void OLED_ClearPoint(u8 x, u8 y)
{
	u8 i, m, n;
	i = y / 8;
	m = y % 8;
	n = 1 << m;
	OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
	OLED_GRAM[x][i] |= n;
	OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
}

// ����

// x,y:Բ������
// r:Բ�İ뾶
void OLED_DrawCircle(u8 x, u8 y, u8 r)
{
	int a, b, num;
	a = 0;
	b = r;
	while (2 * b * b >= r * r)
	{
		OLED_DrawPoint(x + a, y - b);
		OLED_DrawPoint(x - a, y - b);
		OLED_DrawPoint(x - a, y + b);
		OLED_DrawPoint(x + a, y + b);

		OLED_DrawPoint(x + b, y + a);
		OLED_DrawPoint(x + b, y - a);
		OLED_DrawPoint(x - b, y - a);
		OLED_DrawPoint(x - b, y + a);

		a++;
		num = (a * a + b * b) - r * r; // ���㻭�ĵ���Բ�ĵľ���
		if (num > 0)
		{
			b--;
			a--;
		}
	}
}

// m^n
u32 OLED_Pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)
	{
		result *= m;
	}
	return result;
}
// ��ָ��λ����ʾһ���ַ�,���������ַ�
// x:0~127
// y:0~63
void OLED_ShowChar(u8 x, u8 y, u8 chr)
{
	u8 c = 0, i = 0;
	c = chr - ' '; // �õ�ƫ�ƺ��ֵ
	if (x > 130 - 1)
	{
		x = 0;
		y = y + 2;
	}
	OLED_WR_BP(x, y);
	for (i = 0; i < 8; i++)
		OLED_WR_Byte(zf[c * 16 + i], OLED_DATA);
	OLED_WR_BP(x, y + 1);
	for (i = 0; i < 8; i++)
		OLED_WR_Byte(zf[c * 16 + i + 8], OLED_DATA);
}

unsigned int HZ = 0;
// ����GB16�ֿ��ﺺ�ָ���
unsigned int GB16_NUM(void)
{
	unsigned int HZ_NUM;
	unsigned char *PT;
	PT = hz_index;
	while (*PT++ != '\0')
	{
		HZ_NUM++;
	}

	return HZ_NUM / 2;
}
// ��ʾ������
// x,y :�������
// len :���ֵ�λ��
// num:��ֵ(0~4294967295);
// mode:   Ϊ1:��ʾ0   Ϊ0:��ʾ�ո�
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 mode)
{
	u8 t, temp;
	for (t = 0; t < len; t++)
	{
		temp = (num / OLED_Pow(10, len - t - 1)) % 10;
		if (temp == 0)
		{
			if (mode)
				OLED_ShowChar(x + 8 * t, y, '0');
			else
				OLED_ShowChar(x + 8 * t, y, ' ');
			continue;
		}
		else
			OLED_ShowChar(x + 8 * t, y, temp + '0');
	}
}

// ��ʾ��Ӣ���ַ�
void OLED_ShowCH(u8 x, u8 y, u8 *chs)
{
	u32 i = 0;
	u32 j;
	char *m;
	while (*chs != '\0')
	{
		if (*chs > 0xa0) // �������붼�Ǵ���0xa0
		{
			for (i = 0; i < HZ; i++)
			{
				if (x > 112)
				{
					x = 0;
					y = y + 2;
				}
				if ((*chs == hz_index[i * 2]) && (*(chs + 1) == hz_index[i * 2 + 1]))
				{
					OLED_WR_BP(x, y);
					for (j = 0; j < 16; j++)
						OLED_WR_Byte(hz[i * 32 + j], OLED_DATA);
					OLED_WR_BP(x, y + 1);
					for (j = 0; j < 16; j++)
						OLED_WR_Byte(hz[i * 32 + j + 16], OLED_DATA);
					x += 16;
					break;
				}
			}
			chs += 2;
		}
		else
		{
			if (x > 122)
			{
				x = 0;
				y = y + 2;
			}
			m = strchr(zf_index, *chs);
			if (m != NULL)
			{
				OLED_WR_BP(x, y);
				for (j = 0; j < 8; j++)
					OLED_WR_Byte(zf[((u8)*m - ' ') * 16 + j], OLED_DATA);
				OLED_WR_BP(x, y + 1);
				for (j = 0; j < 8; j++)
					OLED_WR_Byte(zf[((u8)*m - ' ') * 16 + j + 8], OLED_DATA);
				x += 8;
			}
			chs++;
		}
	}
}

// ����д�����ݵ���ʼλ��
void OLED_WR_BP(u8 x, u8 y)
{
	OLED_WR_Byte(0xb0 + y, OLED_CMD); // ��������ʼ��ַ
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte((x & 0x0f), OLED_CMD);
}

// x0,y0���������
// x1,y1���յ�����
// BMP[]��Ҫд���ͼƬ����
void OLED_ShowPicture(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
{
	u32 j = 0;
	u8 x = 0, y = 0;
	if (y % 8 == 0)
		y = 0;
	else
		y += 1;
	for (y = y0; y < y1; y++)
	{
		OLED_WR_BP(x0, y);
		for (x = x0; x < x1; x++)
		{
			OLED_WR_Byte(BMP[j], OLED_DATA);
			j++;
		}
	}
}
// OLED�ĳ�ʼ��
void OLED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��A�˿�ʱ��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // �������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �ٶ�50MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);			  // ��ʼ��GPIOD3,6
//	GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_4);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �ٶ�50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);			  // ��ʼ��GPIOD3,6
	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

//	OLED_RST_Set();
//	delay_ms(100);
//	OLED_RST_Clr(); // ��λ
//	delay_ms(200);
//	OLED_RST_Set();

	OLED_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
	OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
	OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
	OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
	OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8, OLED_CMD); // Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
	OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
	OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00, OLED_CMD); //-not offset
	OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
	OLED_WR_Byte(0xF1, OLED_CMD); // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
	OLED_WR_Byte(0x12, OLED_CMD);
	OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
	OLED_WR_Byte(0x40, OLED_CMD); // Set VCOM Deselect Level
	OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02, OLED_CMD); //
	OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
	OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
	OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
	OLED_WR_Byte(0xAF, OLED_CMD);
	OLED_Clear();
}
