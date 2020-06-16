
static unsigned char but_cnt[5]={0};

unsigned int tim_cnt;//счетчик тиков таймера

//—————————————

void Read_Button_State (unsigned char b)

{

        if ((button_state[b]&ST_LOCKED)!=0) return;

        if(Read_Button_Press(b)==ST_UNPRESSED)

        {

                if (but_cnt[b]>0)

                {

                        but_cnt[b]--;

                }

                else

                {

                        if ((button_state[b]&ST_PRESSED)!=0)

                        {

                                button_state[b] |= ST_UNPRESSURE;

                                button_state[b] &= ~ST_PRESSED;

                                button_state[b] |= ST_UNPRESSED;

                        }

                }

        }

        else

        {

                if (but_cnt[b]<5)

                {

                        but_cnt[b]++;

                }

                else

                {

                        if ((button_state[b]&ST_UNPRESSED)!=0)

                        {

                                button_state[b] |= ST_PRESSURE;

                                button_state[b] &= ~ST_UNPRESSED;

                                button_state[b] |= ST_PRESSED;

                        }

                }

        }

}

//—————————————–

void init_button_timer(void)
{

        TIMSK2 |= (1<<TOIE2);        //устанавливаем бит разрешения прерывания 0-ого счетчика по переполнению

        TCCR2B |= (1<<CS22)|(0<<CS21)|(0<<CS20); // устанавливаем предделитель 64

        //тем самым получаем – частота тактирования / предделитель / 256 = 16000000/64/256 = 976,5625 (около милисекунды)

        //делим на 256, так как таймер нулевой всегда считает от 0x00 до 0xFF и это не регулируется никак

}

//——————————————-

ISR (TIMER2_OVF_vect)

{
        Read_Button_State(Button_Right);

        Read_Button_State(Button_Up);

        Read_Button_State(Button_Down);

        Read_Button_State(Button_Left);

        Read_Button_State(Button_Select);

       // readAllSensors();

        tim_cnt++;

        if(tim_cnt>=1000) tim_cnt=0;

}

//—————————————

unsigned char Read_Button_Press(unsigned char b)

{

        switch(b)

        {

                case Button_Right:

                if(digitalRead(Knob_Right)==HIGH)                                                return ST_PRESSED;

                else        return ST_UNPRESSED;

                break;

                case Button_Up:

                if(digitalRead(Knob_Up)==HIGH)                return ST_PRESSED;

                else        return ST_UNPRESSED;

                break;

                case Button_Down:

                if(digitalRead(Knob_Down)==HIGH)                return ST_PRESSED;

                else        return ST_UNPRESSED;

                break;

                case Button_Left:

                if(digitalRead(Knob_Left)==HIGH)        return ST_PRESSED;

                else        return ST_UNPRESSED;

                break;

                case Button_Select:

                if(digitalRead(Knob_Select)==HIGH)        return ST_PRESSED;

                else        return ST_UNPRESSED;

                break;

        }

        return ST_ERROR;

}

void Buttons_Ini(void)

{

        unsigned char i;

        //обнулим счётчики и сбросим статусы

        for (i=0;i<5;i++)

        {

                button_state[i] = ST_UNPRESSED;

        }

        //запустим таймер

        init_button_timer();

}

//—————————————–

void ResetButtonState(unsigned char b, unsigned char st)

{

        button_state[b]  &= ~st;

}

//—————————————–

void SetButtonState(unsigned char b, unsigned char st)

{

        button_state[b]  |= st;

}

//—————————————–
