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

namespace vispoker
{
    /// <summary>
    /// Interaction logic for CardList.xaml
    /// </summary>
    public partial class CardList : UserControl
    {
        private uint count = 0;

        public CardList()
        {
            InitializeComponent();            
        }

        public bool Update(string card_list)
        {
            char[] separators = { '[', ']' };
            string[] card_names = card_list.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            foreach(string card_name in card_names)
            {
                string res_name = ConvertCardname(card_name);
                if (res_name == "unknown")
                    return false;

                Image card_img = new Image();
                BitmapImage bimg = new BitmapImage(new Uri("Resources/" + res_name + ".png", UriKind.Relative));
                card_img.Source = bimg;
                card_img.Margin = new Thickness(count++ * 30, 0, 0, 0);
                card_img.Width = 150;
                card_img.Height = 200;

                cnv_list.Children.Add(card_img);
            }
            return true;
        }

        protected string ConvertCardname(string name)
        {
            char[] separators = { ' ' };
            string[] name_pair = name.Split(separators, StringSplitOptions.RemoveEmptyEntries);
            if (name_pair.Count() != 2)
                return "unknown";
            
            string result;

            if (name_pair[0] == "diamond")
                name_pair[0] = "dia_";
            else
                name_pair[0] += "_";

            result = name_pair[0] + name_pair[1];
            return result;
        }        
    }
}
