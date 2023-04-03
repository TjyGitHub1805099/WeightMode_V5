/**
  *******************************************************************
  * @file    hal_timer.c
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x 定时器程序C文件(抽象层)
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#include "hal_irq_priority.h"
#include "hal_timer.h"
#include "hal_gpio.h"
#include "hal_uart.h"

extern void app_main_task( void );

/**
 * @brief  定时器初始化(默认配置为1us计数一次)
 * @note   系统调度用的定时器需要使用到中断，最后直接启动定时器计数，调试遇到断点时停止计数
 * @param  us:定时时间，单位1us
 * @retval 无
 */
void hal_timer_init( UINT16 us )
{
    // 定时器模块先复位
    drv_timer_deinit( TIMER_BASE );

    //使能定时器时钟
    //定时器DEBUG模式停止计数
    if( (TIMER_BASE == TIM1) || (TIMER_BASE == TIM8) || (TIMER_BASE == TIM15) || (TIMER_BASE == TIM16) || (TIMER_BASE == TIM17) || (TIMER_BASE == TIM20) )
    {
        drv_rcc_apb2_clk_enable( TIMER_BASE_CLK );
        drv_debug_apb2_stop( TIMER_BASE_DEBUG_STOP );
    }
    else
    {
        drv_rcc_apb1_clk_enable( TIMER_BASE_CLK );
        drv_debug_apb1_stop( TIMER_BASE_DEBUG_STOP );
    }

    //定时器初始化
    drv_timer_base_init( TIMER_BASE, 1000000, us - 1, TIM_EDGE_CNT_MODE_UP );

    //定时器中断配置
    drv_nvic_init( TIMER_BASE_IRQn, 0, PRIO_MAIN_TASK );
    drv_nvic_enable( TIMER_BASE_IRQn );
    drv_timer_it_enable( TIMER_BASE, TIM_IT_Update );		// 需要修改中断标志

    //允许计数
    drv_timer_enable( TIMER_BASE );
}

/**
 * @brief  定时器开始计数
 * @retval 无
 */
void hal_timer_start( void )
{
    drv_timer_enable( TIMER_BASE );
}

/**
 * @brief  定时器停止计数
 * @retval 无
 */
void hal_timer_stop( void )
{
    drv_timer_disable( TIMER_BASE );
}

/**
 * @brief  定时器中断服务函数
 * @retval 无
 */
CCMRAM void hal_timer_isr( void )
{    
    drv_timer_clear_it_pending_bit( TIMER_BASE, TIM_IT_Update );

    // 调用主任务函数
    app_main_task( );
    
}

/**
 * \brief  定时器初始化(默认配置为0.1us计数一次)
 * \note   计时时间单位0.1us
 * \return 无
 */
void hal_measure_timer_init( void )
{
    // 定时器模块先复位
    drv_timer_deinit( MEASURE_TIMER_BASE );

    //使能定时器时钟
    //定时器DEBUG模式停止计数
    if( (MEASURE_TIMER_BASE == TIM1) || (MEASURE_TIMER_BASE == TIM8)
        || (MEASURE_TIMER_BASE == TIM15) || (MEASURE_TIMER_BASE == TIM16) || (MEASURE_TIMER_BASE == TIM17) )
    {
        drv_rcc_apb2_clk_enable( MEASURE_TIMER_BASE_CLK );
        drv_debug_apb2_stop( MEASURE_TIMER_BASE_DEBUG_STOP );
    }
    else
    {
        drv_rcc_apb1_clk_enable( MEASURE_TIMER_BASE_CLK );
        drv_debug_apb1_stop( MEASURE_TIMER_BASE_DEBUG_STOP );
    }

    //定时器初始化
    drv_timer_base_init( MEASURE_TIMER_BASE, 1000000, 0xFFFF, TIM_EDGE_CNT_MODE_UP );

    //允许计数
    drv_timer_enable( MEASURE_TIMER_BASE );
}

/**
* \brief  读取时间测试定时器计数值
* \return 计数值
*/
UINT16 hal_measure_timer_get_counter( void )
{
    return (UINT16)MEASURE_TIMER_BASE->CNT.all;
}

/**
* \brief  清时间测试定时器计数值
* \return 计数值
*/
void hal_measure_timer_clear_counter( void )
{
    MEASURE_TIMER_BASE->CNT.all = 0;
}
