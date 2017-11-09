using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vispoker
{
    public class Card
    {
        public Card()
        {}

        public Card(int the_color, int the_number)
        {
            color = the_color;
            number = the_number;
        }

        public bool is_greater(Card other)
        {
            if(number > other.number)
            {
                return true;
            }
            else if(number == other.number)
            {
                if(color < other.color)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else // less than other
            {
                return false;
            }
        }

        public bool is_equal(Card other)
        {
            return color == other.color && number == other.number;
        }

        public bool is_less(Card other)
        {
            return (!is_greater(other) && !is_equal(other));
        }

        public int Number
        {
            get { return number; }
            set { number = value; }
        }

        public int Color
        {
            get { return color; }
            set { color = value; }
        }

        private int color = 1;  // 1 = spade, 2 = heart, 3 = club, 4 = diamond, 5 = joker
        private int number = 1; // 14 = black joker, 15 = red joker
    }
}
