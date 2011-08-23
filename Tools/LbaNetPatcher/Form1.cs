using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LbaNetPatcher
{
    public partial class MainWindow : Form
    {
        private System.Diagnostics.Process _startedprocess;

        public MainWindow()
        {
            _startedprocess = null;

            InitializeComponent();

            try
            {
                System.IO.StreamReader ipfile = new System.IO.StreamReader("patchip.cfg");
                string ipString = ipfile.ReadToEnd();
                ipfile.Close();

                System.Diagnostics.ProcessStartInfo psi =
                    new System.Diagnostics.ProcessStartInfo(@"patchingclient");
                psi.Arguments = " --IcePatch2.Remove=0 --IcePatch2.Endpoints=\"tcp -h "+ipString+" -p 10000\" .";
                psi.CreateNoWindow = true;
                psi.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
                psi.UseShellExecute = true;
                _startedprocess = System.Diagnostics.Process.Start(psi);
            }
            catch (Exception ex)
            {
                labelInfo.Text = "Error during patching: " + ex.Message;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            progressBar.Increment(1);
            if (progressBar.Value == progressBar.Maximum)
                progressBar.Value = 0;

            if (_startedprocess != null && _startedprocess.HasExited)
            {
                if (_startedprocess.ExitCode == 0)
                {
                    labelInfo.Text = "Game updated succesfully.";
                    buttonPlay.Enabled = true;
                    progressBar.Value = progressBar.Maximum;
                }
                else
                {
                    labelInfo.Text = "Error during patching. Please check the file Patching.log for details.";
                    progressBar.Value = 0;
                }

                timer1.Enabled = false;
            }
        }



        private void buttonPlay_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"LBANetGame.exe");
            Application.Exit();
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        public void OnApplicationExit(object sender, EventArgs e)
        {
            try
            {
                if (!_startedprocess.HasExited)
                {
                    _startedprocess.Kill();
                }
            }
            catch (Exception)
            {
            }
        }
    }
}
