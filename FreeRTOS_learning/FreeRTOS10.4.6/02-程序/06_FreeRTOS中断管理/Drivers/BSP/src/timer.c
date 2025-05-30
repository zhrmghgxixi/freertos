#include "timer.h"



/**
******************************************************************************
* @file      ：.\Drivers\BSP\src\timer.c
*              .\Drivers\BSP\inc\timer.h
* @author    ：XRbin
* @version   ：V1.0
* @date      ：2023-07-27
* @brief     ：基本定时器中断练习代码
******************************************************************************
* @attention
*   我的GitHub   ：https://github.com/XR-bin
*   我的gitee    ：https://gitee.com/xrbin
*   我的leetcode ：https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ：TIM6_Init
* @brief    ：对定时器6进行初始化设置
* @param    ：uint16_t arr (重载值)
* @param    ：uint16_t psc (预分频值)
* @retval   ：void
* @details  ：
* @fn       ：定时器6抢占优先级4，子优先级0
************************************************************/
void TIM6_Init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;  /* TIMx配置结构体 */
    NVIC_InitTypeDef NVIC_InitStruct;                /* 中断配置结构体 */

    /* TIMx时钟使能 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    /*TIMx初始化设置*/
    TIM_TimeBaseInitStruct.TIM_Period        = arr;                 /* 重载值(TIMx_ARR寄存器) */
    TIM_TimeBaseInitStruct.TIM_Prescaler     = psc;                 /* 分频(TIMx_PSC寄存器) */
//    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;      /* TDTS = Tck_tim(TIMx_CR1寄存器的第9-8位)(基本定时器没有) */
//    TIM_TimeBaseInitStruct.TIM_CounterMode   = TIM_CounterMode_Up;/* 向上计数(TIMx_CR1寄存器的第4位)(基本定时器只递增) */
    TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);                 /* 初始化TIM6 */

    /* NVIC配置 */
    /* 定时器6中断配置 */
    NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn;            /* 选择TIM6中断 */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;  /* 抢占优先级6 */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;         /* 子优先级0 */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;            /* IRQ通道使能 */
    NVIC_Init(&NVIC_InitStruct);                            /* TIM6中断初始化 */

    /* 允许TIMx更新中断 */
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
    /* 使能TIMx */
    TIM_Cmd(TIM6, ENABLE);
}



/**********************************************************
* @funcName ：TIM6_IRQHandler
* @brief    ：定时器6的中断服务函数
* @param    ：void
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void TIM6_IRQHandler(void)
{
    /* 判断是否定时器6中断 */
    if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        /* 清中断标志位 */
        TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
        /* 紧急事件 */
        GPIOE->ODR ^= (1<<5);     /* LED1翻转 */
        printf("定时器6,抢占优先级为4！！\r\n");
    }
}



/**********************************************************
* @funcName ：TIM7_Init
* @brief    ：对定时器7进行初始化设置
* @param    ：uint16_t arr (重载值)
* @param    ：uint16_t psc (预分频值)
* @retval   ：void
* @details  ：
* @fn       ：定时器7的抢占6，子优先0
************************************************************/
void TIM7_Init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;  /* TIMx配置结构体 */
    NVIC_InitTypeDef NVIC_InitStruct;                /* 中断配置结构体 */

    /* TIMx时钟使能 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

    /*TIMx初始化设置*/
    TIM_TimeBaseInitStruct.TIM_Period        = arr;                 /* 重载值(TIMx_ARR寄存器) */
    TIM_TimeBaseInitStruct.TIM_Prescaler     = psc;                 /* 分频(TIMx_PSC寄存器) */
//    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;      /* TDTS = Tck_tim(TIMx_CR1寄存器的第9-8位)(基本定时器没有) */
//    TIM_TimeBaseInitStruct.TIM_CounterMode   = TIM_CounterMode_Up;/* 向上计数(TIMx_CR1寄存器的第4位)(基本定时器只递增) */
    TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStruct);                 /* 初始化TIM7 */

    /* NVIC配置 */
    /* 定时器7中断配置 */
    NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;            /* 选择TIM7中断 */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 4;  /* 抢占优先级4 */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;         /* 子优先级0 */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;            /* IRQ通道使能 */
    NVIC_Init(&NVIC_InitStruct);                            /* TIM7中断初始化 */

    /* 允许TIMx更新中断 */
    TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
    /* 使能TIMx */
    TIM_Cmd(TIM7, ENABLE);
}



/**********************************************************
* @funcName ：TIM7_IRQHandler
* @brief    ：定时器7的中断服务函数
* @param    ：void
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void TIM7_IRQHandler(void)
{
    /* 判断是否定时器7中断 */
    if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {
        /* 清中断标志位 */
        TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
        /* 紧急事件 */
        GPIOB->ODR ^= (1<<5);     /* LED0翻转 */
        printf("定时器7,抢占优先级为6！！\r\n");
    }
}




