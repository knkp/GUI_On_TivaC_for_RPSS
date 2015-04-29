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

Canvas(g_sHeading, &g_sBackground, 0, &g_sPushBtn,
       &g_sKentec320x240x16_SSD2119, 0, 0, 320, 23,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE | CANVAS_STYLE_TEXT),
       ClrBlack, ClrWhite, ClrRed, g_psFontCm20, "LED Control", 0, 0);

Canvas(g_sBackground, WIDGET_ROOT, 0, &g_sHeading,
       &g_sKentec320x240x16_SSD2119, 0, 23, 320, (240 - 23),
       CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0);

RectangularButton(g_sPushBtn, &g_sHeading, 0, 0,
                  &g_sKentec320x240x16_SSD2119, 60, 60, 200, 40,
                  (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
                   PB_STYLE_FILL), ClrGray, ClrWhite, ClrRed, ClrRed,
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

    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sBackground);

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
	GrContextFontSet(&sContext, &g_sFontCmss30b);
	GrStringDraw(&sContext, "Texas", -1, 110, 2, 0);
	GrStringDraw(&sContext, "Instruments", -1, 80, 32, 0);
	GrStringDraw(&sContext, "Graphics", -1, 100, 62, 0);
	GrStringDraw(&sContext, "Lab", -1, 135, 92, 0);
	GrContextForegroundSet(&sContext, ClrWhite);
	GrRectDraw(&sContext, &sRect);
	GrFlush(&sContext);

	while(notTouched){
		wait_for_touch();
	}

	notTouched = 1;
}

void display_outro(){

}

void display_waiting_time(){

}
static void ClrScreen()
{
   sRect.i16XMin = 0;
   sRect.i16YMin = 0;
   sRect.i16XMax = 319;
   sRect.i16YMax = 239;
   GrContextForegroundSet(&sContext, ClrBlack);
   GrRectFill(&sContext, &sRect);
   GrFlush(&sContext);
}
