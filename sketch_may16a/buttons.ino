void Buttons_Ini(void)

{

  unsigned char i;

  //обнулим счётчики и сбросим статусы

  for (i = 0; i < 5; i++)

  {

    button_state[i] = ST_UNPRESSED;

  }

}

unsigned char Read_Button_Press(unsigned char b)

{

  switch (b)

  {

    case Button_Right:

      if (digitalRead(Knob_Right) == HIGH)                                                return ST_PRESSED;

      else        return ST_UNPRESSED;

      break;

    case Button_Up:

      if (digitalRead(Knob_Up) == HIGH)                return ST_PRESSED;

      else        return ST_UNPRESSED;

      break;

    case Button_Down:

      if (digitalRead(Knob_Down) == HIGH)                return ST_PRESSED;

      else        return ST_UNPRESSED;

      break;

    case Button_Left:

      if (digitalRead(Knob_Left) == HIGH)        return ST_PRESSED;

      else        return ST_UNPRESSED;

      break;

    case Button_Select:

      if (digitalRead(Knob_Select) == HIGH)        return ST_PRESSED;

      else        return ST_UNPRESSED;

      break;

  }

  return ST_ERROR;

}

void Read_Button_State (unsigned char b)

{

  if ((button_state[b]&ST_LOCKED) != 0) return;

  if (Read_Button_Press(b) == ST_UNPRESSED)

  {

    if (but_cnt[b] > 0)

    {

      but_cnt[b]--;

    }

    else

    {

      if ((button_state[b]&ST_PRESSED) != 0)

      {

        button_state[b] |= ST_UNPRESSURE;

        button_state[b] &= ~ST_PRESSED;

        button_state[b] |= ST_UNPRESSED;

      }

    }

  }

  else

  {

    if (but_cnt[b] < 5)

    {

      but_cnt[b]++;

    }

    else

    {

      if ((button_state[b]&ST_UNPRESSED) != 0)

      {

        button_state[b] |= ST_PRESSURE;

        button_state[b] &= ~ST_UNPRESSED;

        button_state[b] |= ST_PRESSED;

      }

    }

  }

}

void ResetButtonState(unsigned char b, unsigned char st)

{

  button_state[b]  &= ~st;

}

//—————————————–

void SetButtonState(unsigned char b, unsigned char st)

{

  button_state[b]  |= st;

}

void CheckButtons(void) {

  Read_Button_State(Button_Right);

  Read_Button_State(Button_Up);

  Read_Button_State(Button_Down);

  Read_Button_State(Button_Left);

  Read_Button_State(Button_Select);

}
