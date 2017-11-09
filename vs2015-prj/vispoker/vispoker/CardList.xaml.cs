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
            string[] card_names = card_list.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            int next_x = 0;
            bool is_card_continue = false;
            foreach(string card_name in card_names)
            {
                string res_name = ConvertCardname(card_name);
                if (res_name != "unknown")
                {
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
                else
                {
                    if (card_name != "!Break_Cards_Continue!")
                    {
                        string text = card_name;
                        Label label = new Label();
                        label.Content = text;
                        label.Height = 30;

                        label.Margin = new Thickness(next_x, 0, 0, 0);

                        next_x += (int)50;
                        cnv_list.Children.Add(label);
                    }
                    is_card_continue = false;                    
                }
            }
            return true;
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
