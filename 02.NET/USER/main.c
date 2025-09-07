#include "git.h"


// �����ʱ���趨
static Timer task1_id;
static Timer task2_id;
static Timer task3_id;
extern u8 time25ms;

// ��ȡȫ�ֱ���
const char *topics[] = {S_TOPIC_NAME};

// Ӳ����ʼ��
void Hardware_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�

    delay_init();                                   // ��ʱ������ʼ��
    GENERAL_TIM_Init(TIM_4, 0, 1);
   
    while (Reset_Threshole_Value(&threshold_value_init, &device_state_init) != MY_SUCCESSFUL)
        delay_ms(5); // ��ʼ����ֵ
  

}
// �����ʼ��
void Net_Init()
{

#if OLED // OLED�ļ�����
    // дOLED����
		LCD1602_Show_Str(2, 0, "WIFI  ... ");
		LCD1602_Show_Str(2, 1, "COUNT ...");
#endif
    ESP8266_Init();          // ��ʼ��ESP8266
   
		
		LCD1602_ClearScreen(); // ����
}

// ����1
void task1(void)
{
	//1�������
 	Automation_Close();
	Update_oled_massage();   // ����OLED
	
}
// ����2
void task2(void)
{
// �豸����
#if NETWORK_CHAEK
    if (Connect_Net == 0) {
			
#if OLED // OLED�ļ�����
		LCD1602_Show_Str(2, 0, "WIFI  ... ");
		LCD1602_Show_Str(2, 1, "COUNT ...");
#endif
        ESP8266_Init();          // ��ʼ��ESP8266
        while (DevLink()) // ����OneNET
            delay_ms(300);
        while (Subscribe(topics, 1)) // ��������
            delay_ms(300);
        Connect_Net = 60; // �����ɹ�
    }
#endif

    Read_Data(&Data_init);   // ���´���������
   
    Update_device_massage(); // �����豸
                             // BEEP= ~BEEP;
    State = ~State;
}
// ����3
void task3(void)
{
   if (Connect_Net && Data_init.App == 0) {
        //Data_init.App = 1;
   }
}
// �����ʼ��
void SoftWare_Init(void)
{
    // ��ʱ����ʼ��
    timer_init(&task1_id, task1, 1000, 1); // 1sִ��һ��
    timer_init(&task2_id, task2, 60, 1);  // 100msִ��һ��
    timer_init(&task3_id, task3, 4000, 1); // 2.5sִ��һ��
 
}
// ������
int main(void)
{

    unsigned char *dataPtr = NULL;
    SoftWare_Init(); // �����ʼ��
    Hardware_Init(); // Ӳ����ʼ��

    Net_Init(); // �����ʼ
    TIM_Cmd(TIM4, ENABLE); // ʹ�ܼ�����
	
		Get_Maopi(); // ����
    delay_ms(1000);
    Get_Maopi(); // ����
    while (1) {

        // �߳�
        timer_loop(); // ��ʱ��ִ��
        // ���ڽ����ж�
        dataPtr = ESP8266_GetIPD(0);
     
    }
}

