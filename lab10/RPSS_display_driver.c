#include "RPSS_display_driver.h"
#include <stdint.h>
#include <stdbool.h>
//#include "image_example.h"  // this is the default image for the example -- Stephen Copeland (4/28/2015)
#include "alcoholPic.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/pushbutton.h"
#include "Kentec320x240x16_ssd2119_8bit.h"
#include "touch.h"

extern tCanvasWidget g_sBackground;
extern tPushButtonWidget g_sPushBtn;

extern const uint8_t alcoholPic[];
tContext sContext;
tRectangle sRect;
int notTouched = 1;

static void ClrScreen(void);

static void OnButtonPress(tWidget *pWidget);

/*
Canvas(g_sHeading, &g_sBackground, 0, &g_sPushBtn,
       &g_sKentec320x240x16_SSD2119, 0, 0, 320, 23,
     //  (CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE | CANVAS_STYLE_TEXT),
       0,ClrBlack, ClrWhite, ClrRed, g_psFontCm20, "LED Control", 0, 0);
*/

/*
Canvas(g_sBackground, WIDGET_ROOT, 0, &g_sHeading,
       &g_sKentec320x240x16_SSD2119, 0, 23, 320, (240 - 23),
       CANVAS_STYLE_FILL, //ClrBlack,
	   0,0, 0, 0, 0, 0, 0);*/

// changed parent to WIDGET_ROOT to place rectangular button at source, of widget tree,
//also not drawing associated variables or values, also setting button size to whole screen.

// note what might be called the "handle" for the object is g_sPushBtn, and the callback function is OnButtonPress
RectangularButton(g_sPushBtn, WIDGET_ROOT, 0, 0,
                  &g_sKentec320x240x16_SSD2119, //60, 60, 200, 40,
				  0, 0, 320,240,
                  //(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
                 //  PB_STYLE_FILL),
				  0,
				   ClrGray, ClrWhite, ClrRed, ClrRed,
                   g_psFontCmss22b, "Toggle red LED", 0, 0, 0, 0, OnButtonPress);

bool g_RedLedOn = false;


int init_display(){

	sRect.i16XMin = 1;
	sRect.i16YMin = 1;
	sRect.i16XMax = 318;
	sRect.i16YMax = 238;


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);

    Kentec320x240x16_SSD2119Init();
    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);
    ClrScreen();

    TouchScreenInit();

    TouchScreenCallbackSet(WidgetPointerMessage);

    //WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sBackground);
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sPushBtn);

    WidgetPaint(WIDGET_ROOT);

    return 0;

}


static void OnButtonPress(tWidget *pWidget)
{
    g_RedLedOn = !g_RedLedOn;

    if(g_RedLedOn)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
    }

    // break loop, stop proessing touches
    notTouched = 0;
}

void wait_for_touch(){
	WidgetMessageQueueProcess();
}

void display_intro(){
	ClrScreen();
    GrImageDraw(&sContext, alcoholPic, 0, 0);
    GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss40b);
	GrStringDraw(&sContext, "Welome to", -1, 50, 25, 0);
	GrStringDraw(&sContext, "RPSS!", -1, 100, 75, 0);
	GrStringDraw(&sContext, "Tap to", -1, 85, 130, 0);
	GrStringDraw(&sContext, "continue", -1, 75, 180, 0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);

	while(notTouched){
		wait_for_touch();
	}

	notTouched = 1;
}

void display_outro(){
	ClrScreen();
    GrImageDraw(&sContext, alcoholPic, 0, 0);
    GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss40b);
	GrStringDraw(&sContext, "See you next", -1, 35,75,0);
	GrStringDraw(&sContext, "time!", -1, 110, 105,0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);
	SysCtlDelay(SysCtlClockGet()*3/2);
}

void display_waiting_time(){
	ClrScreen();
    GrImageDraw(&sContext, alcoholPic, 0, 0);
    GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	//GrStringDraw(&sContext, "Welome to", -1, 50, 25, 0);
	GrStringDraw(&sContext, "Looks like you", -1, 50, 50, 0);
	GrStringDraw(&sContext, "need a ride home", -1, 45, 85, 0);
	GrStringDraw(&sContext, "A taxi is on the way!", -1, 10, 180, 0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);
}

void display_welcome(){
	ClrScreen();
    GrImageDraw(&sContext, alcoholPic, 0, 0);
    GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	GrStringDraw(&sContext, "Thank You", -1, 75,35,0);
	GrStringDraw(&sContext, "for choosing RPSS!", -1, 25, 65, 0);
	GrStringDraw(&sContext, "Please scan your", -1, 45, 140, 0);
	GrStringDraw(&sContext, "finger to get started",-1,10,170,0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);
}

void display_database_check(){
	ClrScreen();
	GrImageDraw(&sContext, alcoholPic, 0, 0);
	GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	GrStringDraw(&sContext, "Time to check", -1, 60,35,0);
	GrStringDraw(&sContext, "your blood alcohol", -1, 30, 65, 0);
	GrStringDraw(&sContext, "content, please use", -1, 35, 95, 0);
	GrStringDraw(&sContext, "a straw to breath on",-1,10,125,0);
	GrStringDraw(&sContext, "the sensor",-1,100,155,0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);
}

void display_release_items(){
	ClrScreen();
	GrImageDraw(&sContext, alcoholPic, 0, 0);
	GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	//GrStringDraw(&sContext, "Time to check", -1, 60,35,0);
	GrStringDraw(&sContext, "Your cabinet is open", -1, 15, 65, 0);
	GrStringDraw(&sContext, "you may now remove", -1, 10, 95, 0);
	GrStringDraw(&sContext, "your items",-1,100,125,0);
	//GrStringDraw(&sContext, "the sensor",-1,100,155,0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);
}

void display_registration(){
	ClrScreen();
	GrImageDraw(&sContext, alcoholPic, 0, 0);
	GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	//GrStringDraw(&sContext, "Time to check", -1, 60,35,0);
	GrStringDraw(&sContext, "Please place your", -1, 30, 65, 0);
	GrStringDraw(&sContext, "items in the", -1, 55, 95, 0);
	GrStringDraw(&sContext, "open cabinet",-1,55,125,0);
	//GrStringDraw(&sContext, "your items",-1,100,125,0);
	//GrStringDraw(&sContext, "the sensor",-1,100,155,0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);
}

void display_maintenance_mode(){
	ClrScreen();
	GrImageDraw(&sContext, alcoholPic, 0, 0);
	GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	//GrStringDraw(&sContext, "Time to check", -1, 60,35,0);
	GrStringDraw(&sContext, "System Maintenance", -1, 15, 65, 0);
	//GrStringDraw(&sContext, "items in the", -1, 55, 95, 0);
	//GrStringDraw(&sContext, "open cabinet",-1,55,125,0);
	//GrStringDraw(&sContext, "your items",-1,100,125,0);
	//GrStringDraw(&sContext, "the sensor",-1,100,155,0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);

}

void display_error_state(){
	ClrScreen();
	GrImageDraw(&sContext, alcoholPic, 0, 0);
	GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	//GrStringDraw(&sContext, "Time to check", -1, 60,35,0);
	GrStringDraw(&sContext, "System Error", -1, 60, 65, 0);
	//GrStringDraw(&sContext, "items in the", -1, 55, 95, 0);
	//GrStringDraw(&sContext, "open cabinet",-1,55,125,0);
	//GrStringDraw(&sContext, "your items",-1,100,125,0);
	//GrStringDraw(&sContext, "the sensor",-1,100,155,0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);
}

void display_failed_to_get_breath(){
	ClrScreen();
    GrImageDraw(&sContext, alcoholPic, 0, 0);
    GrFlush(&sContext);

	GrContextForegroundSet(&sContext, ClrBlue);
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	//GrStringDraw(&sContext, "Welome to", -1, 50, 25, 0);
	GrStringDraw(&sContext, "The breathalyzer", -1, 50, 50, 0);
	GrStringDraw(&sContext, "test was not used", -1, 45, 85, 0);
	GrStringDraw(&sContext, "Please try again", -1, 50, 180, 0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);
	SysCtlDelay(SysCtlClockGet()*3/2);
}

static void ClrScreen(){

   sRect.i16XMin = 0;
   sRect.i16YMin = 0;
   sRect.i16XMax = 319;
   sRect.i16YMax = 239;
   GrContextForegroundSet(&sContext, ClrBlack);
   GrRectFill(&sContext, &sRect);
   GrFlush(&sContext);
}
