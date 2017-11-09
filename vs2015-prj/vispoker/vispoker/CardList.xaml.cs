using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Text.RegularExpressions;

namespace vispoker
{
    /// <summary>
    /// Interaction logic for CardList.xaml
    /// </summary>
    public partial class CardList : UserControl
    {
        public CardList()
        {
            InitializeComponent();
        }

        public bool Update(string card_list)
        {
            char[] separators = { ';' };
            card_list = card_list.Replace(" ", ";!Break_Cards_Continue!;");
            card_list = card_list.Replace(",", ";!Break_Cards_Continue!;");
            string[] card_names = card_list.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            int next_x = 0;
            bool is_card_continue = false;

            CardSet curr_cards = null;
            foreach(string card_name in card_names)
            {
                Card new_card;
                if(CardFromString(out new_card, card_name))
                {
                    if(is_card_continue)
                    {
                        curr_cards.cards.Add(new_card);
                        curr_cards.sort_desc();
                    }
                    else
                    {
                        curr_cards = new CardSet();
                        curr_cards.cards.Add(new_card);
                        is_card_continue = true;
                    }
                }
                else
                {
                    is_card_continue = false;
                    if (null != curr_cards)
                    {
                        foreach(Card card in curr_cards.cards)
                        {
                            string res_name = CardImageName(card);

                            Image card_img = new Image();
                            BitmapImage bimg = new BitmapImage(new Uri("Resources/" + res_name + ".png", UriKind.Relative));
                            card_img.Source = bimg;

                            card_img.Width = 150;
                            card_img.Height = 200;

                            if (!is_card_continue)
                            {
                                card_img.Margin = new Thickness(next_x, 0, 0, 0);
                                next_x += 150;
                                is_card_continue = true;
                            }
                            else
                            {
                                card_img.Margin = new Thickness(next_x - 120, 0, 0, 0);
                                next_x += 30;
                            }

                            cnv_list.Children.Add(card_img);
                        }

                        is_card_continue = false;
                        curr_cards = null;
                    }

                    if (card_name != "!Break_Cards_Continue!")
                    {
                        string text = card_name;
                        Label label = new Label();
                        label.Content = text;
                        label.Height = 30;

                        label.Margin = new Thickness(next_x, 0, 0, 0);

                        next_x += (int)30;
                        cnv_list.Children.Add(label);
                    }
                }
            }

            if(is_card_continue)
            {
                is_card_continue = false;
                foreach (Card card in curr_cards.cards)
                {
                    string res_name = CardImageName(card);

                    Image card_img = new Image();
                    BitmapImage bimg = new BitmapImage(new Uri("Resources/" + res_name + ".png", UriKind.Relative));
                    card_img.Source = bimg;

                    card_img.Width = 150;
                    card_img.Height = 200;

                    if (!is_card_continue)
                    {
                        card_img.Margin = new Thickness(next_x, 0, 0, 0);
                        next_x += 150;
                        is_card_continue = true;
                    }
                    else
                    {
                        card_img.Margin = new Thickness(next_x - 120, 0, 0, 0);
                        next_x += 30;
                    }

                    cnv_list.Children.Add(card_img);
                }
            }
            
            return true;
        }

        protected bool CardFromString(out Card card, string card_name)
        {
            card = new Card();
            char[] separators = { '-' };
            string[] name_pair = card_name.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            if (name_pair.Count() != 2)
            {
                if (name_pair.Count() == 1)
                {
                    if (name_pair[0] == "BJoker" || name_pair[0] == "BJ" ||
                        name_pair[0] == "dawang" || name_pair[0] == "Dawang" ||
                        name_pair[0] == "DaWang" || name_pair[0] == "DW" ||
                        name_pair[0] == "dw" || name_pair[0] == "Dw")
                    {
                        card.Color = 5;
                        card.Number = 15;
                        return true;
                    }
                    else if (name_pair[0] == "SJoker" || name_pair[0] == "SJ" ||
                           name_pair[0] == "xiaowang" || name_pair[0] == "Xiaowang" ||
                           name_pair[0] == "XiaoWang" || name_pair[0] == "XW" ||
                           name_pair[0] == "xw" || name_pair[0] == "xw")
                    {
                        card.Color = 5;
                        card.Number = 14;
                        return true;
                    }
                    else
                    {
                        card = null;
                        return false;
                    }
                }
                else
                {
                    card = null;
                    return false;
                }
            }
            
            if (name_pair[0] == "1")
            {
                card.Color = 1;
            }
            else if (name_pair[0] == "2")
            {
                card.Color = 2;
            }
            else if (name_pair[0] == "3")
            {
                card.Color = 3;
            }
            else if (name_pair[0] == "4")
            {
                card.Color = 4;
            }
            else if (name_pair[1] == "BJoker" || name_pair[1] == "BJ" ||
                name_pair[1] == "dawang" || name_pair[1] == "Dawang" ||
                name_pair[1] == "DaWang" || name_pair[1] == "DW" ||
                name_pair[1] == "dw" || name_pair[1] == "Dw")
            {
                card.Color = 5;
                card.Number = 15;
                return true;
            }
            else if (name_pair[1] == "SJoker" || name_pair[1] == "SJ" ||
                name_pair[1] == "xiaowang" || name_pair[1] == "Xiaowang" ||
                name_pair[1] == "XiaoWang" || name_pair[1] == "XW" ||
                name_pair[1] == "xw" || name_pair[1] == "xw")
            {
                card.Color = 5;
                card.Number = 14;
                return true;
            }
            else
            {
                card = null;
                return false;
            }

            if (name_pair[1] == "1")
            {   
                card.Number = 1;
            }
            else if (name_pair[1] == "2")
            {
                card.Number = 2;
            }
            else if (name_pair[1] == "3")
            {
                card.Number = 3;
            }
            else if (name_pair[1] == "4")
            {
                card.Number = 4;
            }
            else if (name_pair[1] == "5")
            {
                card.Number = 5;
            }
            else if (name_pair[1] == "6")
            {
                card.Number = 6;
            }
            else if (name_pair[1] == "7")
            {
                card.Number = 7;
            }
            else if (name_pair[1] == "8")
            {
                card.Number = 8;
            }
            else if (name_pair[1] == "9")
            {
                card.Number = 9;
            }
            else if (name_pair[1] == "10")
            {
                card.Number = 10;
            }
            else if (name_pair[1] == "11" ||
                name_pair[1] == "j")
            {
                card.Number = 11;
            }
            else if (name_pair[1] == "12" ||
                name_pair[1] == "q")
            {
                card.Number = 12;
            }
            else if (name_pair[1] == "13" ||
                name_pair[1] == "k")
            {
                card.Number = 13;
            }
            else
            {
                card = null;
                return false;
            }

            return true;
        }

        protected string CardImageName(Card card)
        {
            string name = String.Empty;
            switch(card.Color)
            {
                case 1:
                    name = "spade_";
                    break;
                case 2:
                    name = "heart_";
                    break;
                case 3:
                    name = "club_";
                    break;
                case 4:
                    name = "dia_";
                    break;
            }

            if(card.Number <= 0 || card.Number >15)
            {
                name = "unknown";
            }
            else if(card.Number == 1)
            {
                name += "ace";
            }
            else if(card.Number >= 2 && card.Number <= 10)
            {
                name += card.Number.ToString();
            }
            else if(card.Number == 11)
            {
                name += "jack";
            }
            else if (card.Number == 12)
            {
                name += "queen";
            }
            else if (card.Number == 13)
            {
                name += "king";
            }

            if(card.Number == 14)
            {
                name = "black_joker";
            }
            else if(card.Number == 15)
            {
                name = "red_joker";
            }

            return name;
        }

        protected string ConvertCardname(string name)
        {
            char[] separators = { '-' };
            string[] name_pair = name.Split(separators, StringSplitOptions.RemoveEmptyEntries);
            if (name_pair.Count() != 2)
                return "unknown";
            
            string result;

            if (name_pair[0] == "1")
            {
                name_pair[0] = "spade_";
            }
            else if (name_pair[0] == "2")
            {
                name_pair[0] = "heart_";
            }
            else if (name_pair[0] == "3")
            {
                name_pair[0] = "club_";
            }
            else if (name_pair[0] == "4")
            {
                name_pair[0] = "dia_";
            }
            else if (name_pair[1] == "BJoker" || name_pair[1] == "BJ" ||
                name_pair[1] == "dawang" || name_pair[1] == "Dawang" ||
                name_pair[1] == "DaWang" || name_pair[1] == "DW" ||
                name_pair[1] == "dw" || name_pair[1] == "Dw")
            {
                name_pair[0] = "red_";
                name_pair[1] = "joker";
            }
            else if (name_pair[1] == "SJoker" || name_pair[1] == "SJ" ||
                name_pair[1] == "xiaowang" || name_pair[1] == "Xiaowang" ||
                name_pair[1] == "XiaoWang" || name_pair[1] == "XW" ||
                name_pair[1] == "xw" || name_pair[1] == "xw")
            {
                name_pair[0] = "black_";
                name_pair[1] = "joker";
            }
            else
                return "unknown";

            if (name_pair[1] == "1")
            {
                name_pair[1] = "ace";
            }
            else if(name_pair[1] == "11" ||
                name_pair[1] == "j")
            {
                name_pair[1] = "jack";
            }
            else if (name_pair[1] == "12" ||
                name_pair[1] == "q")
            {
                name_pair[1] = "queen";
            }
            else if (name_pair[1] == "13" ||
                name_pair[1] == "k")
            {
                name_pair[1] = "king";
            }

            result = name_pair[0] + name_pair[1];
            return result;
        }        
    }
}
