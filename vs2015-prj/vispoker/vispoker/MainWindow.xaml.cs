using System;
using System.IO;
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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            
        }

        private void ParseLine(string line)
        {
            if (line.Length <= 0)
                return;
            
            CardList clist = new CardList();
            if (clist.Update(line))
            {
                clist.Height = 200;
                pnl_cardset.Children.Add(clist);
            }
            else
            {
                string text = line;
                Label label = new Label();
                label.Content = text;
                label.Height = 30;
                pnl_cardset.Children.Add(label);
            }
        }

        private void txt_cards_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.Key == Key.Enter)
            {
                
                ParseLine(txt_cards.Text);
                txt_cards.Text = String.Empty;
            }
        }

        private void srv_cardset_Drop(object sender, DragEventArgs e)
        {
            if (!e.Data.GetDataPresent("FileNameW"))
                return;

            String[] filenames = e.Data.GetData("FileNameW") as String[];
            if (filenames.Count() <= 0)
                return;

            foreach (String filename in filenames)
            {
                if (!File.Exists(filename))
                    continue;

                FileStream fs = null;
                StreamReader sr = null;
                try
                {
                    fs = new FileStream(filenames[0], FileMode.Open, FileAccess.Read);
                    sr = new StreamReader(fs, Encoding.UTF8);
                    fs.Seek(0, SeekOrigin.Begin);
                    string line;
                    while(null != (line = sr.ReadLine()))
                    {
                        ParseLine(line);
                    }
                }
                catch(Exception)
                {
                }
                finally
                {
                    sr.Close();
                    fs.Close();
                }
            }
        }
    }
}
