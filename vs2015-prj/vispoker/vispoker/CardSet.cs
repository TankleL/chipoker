using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vispoker
{
    public class CardSet
    {
        public static int cmp_desc(Card left, Card right)
        {
            if (left.is_greater(right))
                return -1;
            else if (left.is_equal(right))
                return 0;
            return 1;
        }

        public static int cmp_incr(Card left, Card right)
        {
            if (left.is_greater(right))
                return 1;
            else if (left.is_equal(right))
                return 0;
            return -1;
        }

        public void sort_incr()
        {
            cards.Sort(cmp_incr);
        }

        public void sort_desc()
        {
            cards.Sort(cmp_desc);
        }

        public List<Card> cards = new List<Card>();
    }
}
