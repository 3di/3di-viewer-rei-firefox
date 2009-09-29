/*
 * Copyright (c) 2009, 3Di, Inc. (http://3di.jp/) and contributors.
 * See CONTRIBUTORS.TXT for a full list of copyright holders.
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Threading;
using System.IO;
using System.Net;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Xml;
using Microsoft.Win32;
using OpenViewer;
using OpenMetaverse;

namespace OpenViewer.bootstrap
{
    public class Bootstrap
    {
        private static int numberOfInstanceInCurrentClr = 0;
        private static Object numberOfInstanceInCurrentClrLock = new Object();
        
        private readonly IntPtr Handle;
        private readonly Viewer OV;
        private readonly Version version = VersionInfo.version;
        private readonly OpenViewerConfigSource config = new OpenViewerConfigSource();
        private readonly UUID keepaliveUUID = OpenMetaverse.UUID.Random();
        private System.Threading.Timer keepAliveTimer;
        private Thread loadThread;
        private bool isStarted = false;
        private Form form;
        private int width;
        private int height;
        private string backgroundColor;
        private string initBackgroundURL;
        private Bitmap initBackgroundBitmap;
        private string requireVersion;

        [DllImport("user32.dll")]
        static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        public Control Control
        {
            get
            {
                if (form == null)
                {
                    form = new Form();
                    form.Size = new Size(width, height);
                    form.Location = new Point(0, 0);
                    form.StartPosition = FormStartPosition.Manual;
                    form.FormBorderStyle = FormBorderStyle.None;
                    form.BackColor = Color.White;
                    if (!String.IsNullOrEmpty(backgroundColor) && backgroundColor.Substring(0, 1) == "#")
                    {
                        form.BackColor = Color.FromArgb(0xFF,Util.FromString(backgroundColor));
                    }
                    SetParent(form.Handle, Handle);
                }
                return form;
            }
        }
        
        public System.Windows.Forms.Control.ControlCollection Controls
        {
            get { return this.Control.Controls; }
        }

        public int Width
        {
            get { return width; }
        }

        public int Height
        {
            get { return height; }
        }

        public string BackgroundColor
        {
            get
            {
                return backgroundColor;
            }
            set
            {
                backgroundColor = value;
            }
        }

        public string InitBackgroundURL
        {
            get {
                return initBackgroundURL;
            }
            set {
                initBackgroundURL = value;
            }
        }
        
        private Bitmap InitBackgroundBitmap
        {
            get
            {
                if (initBackgroundBitmap == null)
                {
                    Bitmap bitmap = null;
                    try
                    {
                        if (!String.IsNullOrEmpty(initBackgroundURL))
                        {
                            string local = Util.GuiFolder + UUID.Random().ToString();
                            Util.DownloadImage(initBackgroundURL, local);
                            if (File.Exists(local + ".png"))
                            {
                                bitmap = new Bitmap(local + ".png");
                            }
                        }
                    }
                    catch
                    {
                    }
                    if (bitmap == null)
                    {
                        bitmap = new Bitmap(Util.ApplicationDataDirectory + @"\media\gui\background\login_background.png");
                    }
                    initBackgroundBitmap = bitmap;
                }
                return initBackgroundBitmap;
            }
        }

        public string RequireVersion
        {
            get {
                return requireVersion;
            }
            set {
                requireVersion = value;
            }
        }

        public bool IsStarted
        {
            get { return isStarted; }
        }

        public Bootstrap(Viewer OV, IntPtr Handle, int width, int height)
        {
            this.OV = OV;
            this.Handle = Handle;
            this.width = width;
            this.height = height;
        }
        
        private bool InitializeVersion()
        {
            return true;
        }

        private void VersionCheckError(string mesg, string title)
        {
            System.Windows.Forms.MessageBox.Show(mesg, title, System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
        }

        private bool IsVersionRequirementSatisfied(string requirement)
        {
            try
            {
                return new Version(requirement.Replace(",", ".")) <= version;
            }
            catch
            {
                return true;
            }
        }

        private bool CheckCurrentVersion(string xml)
        {
            string description = null;
            string title = null;
            Version currentReleaseVersion = null;

            try
            {
                XmlDocument xmlDoc = new XmlDocument();

                xmlDoc.LoadXml(xml);

                foreach (XmlNode toplevel in xmlDoc.ChildNodes)
                {
                    if (toplevel.Name == "OpenViewer")
                    {
                        foreach (XmlNode secondary in toplevel.ChildNodes)
                        {
                            if (secondary.Name == "LatestRelease")
                            {
                                XmlAttribute host = secondary.Attributes["host"];
                                
                                if (host == null || String.IsNullOrEmpty(host.Value))
                                    continue;
                                if (host.Value != "Firefox")
                                    continue;

                                foreach (XmlNode leaf1 in secondary.ChildNodes)
                                {
                                    if (leaf1.Name == "Type" && leaf1.InnerText.Equals("stable", StringComparison.OrdinalIgnoreCase))
                                    {
                                        foreach (XmlNode leaf2 in secondary.ChildNodes)
                                        {
                                            if (leaf2.Name == "Version")
                                            {
                                                currentReleaseVersion = new Version(leaf2.InnerText.Replace(",", "."));
                                            }
                                            if (leaf2.Name == "Description")
                                            {
                                                description = leaf2.InnerText;
                                            }
                                            if (leaf2.Name == "Title")
                                            {
                                                title = leaf2.InnerText;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (currentReleaseVersion != null && version < currentReleaseVersion)
                {
                    if (!String.IsNullOrEmpty(description))
                    {
                        if (title == null)
                            title = "3Di OpenViewer Update";
                        System.Windows.Forms.MessageBox.Show(description, title, System.Windows.Forms.MessageBoxButtons.OK);
                        return false;
                    }
                }
            }
            catch (Exception e)
            {
                VersionCheckError(e.Message, "バージョンを確認中にエラーが発生しました");
                return false;
            }
            return true;
        }

        private void VersionCheckCallback(Object sender, DownloadStringCompletedEventArgs e)
        {
            if (e.Error == null)
            {
                CheckCurrentVersion(e.Result);
            }
            else
            {
            }
        }

        private bool ShowVersionCheckWindow(string uriString)
        {
            Uri uri = new Uri(uriString);
            WebClient client = new WebClient();
            try
            {
                client.DownloadStringCompleted += new DownloadStringCompletedEventHandler(VersionCheckCallback);
                client.DownloadStringAsync(uri);
            }
            catch (Exception e)
            {
                VersionCheckError(e.Message, "最新バージョンを問い合わせ中にエラーが発生しました");
                return false;
            }
            return true;
        }

        public bool CheckDriveSize()
        {
            bool flag = true;

            try
            {
                string driveName = Path.GetPathRoot(Application.ExecutablePath);
                DriveInfo currentDrive = new DriveInfo(driveName);

                // to MB.
                long size = currentDrive.TotalFreeSpace / (1024 * 1024);

                DialogResult res = DialogResult.OK;
                if (size < 500) // 500MB
                {
                    res = System.Windows.Forms.MessageBox.Show("HDDの空き容量が足りないために正常に起動できませんでした。", "起動エラー");
                    res = DialogResult.Cancel;
                }
                else if (size < 3 * 1024) // 3GB
                {
                    res = System.Windows.Forms.MessageBox.Show("正常に動作するために必要なHDD容量（3GB）が足りていません\nこのまま起動しますか？", "起動確認", MessageBoxButtons.OKCancel);
                }

                if (res != DialogResult.OK)
                    flag = false;
            }
            catch (Exception e)
            {
                VUtil.LogConsole(this.ToString(), "CheckDriveSize:" + e.Message);
            }

            return flag;
        }

        public void SetupConfig()
        {
            try
            {
                bool readConfig = false;
                string iniconfig = Path.Combine(Util.ConfigFolder, "OpenViewer.ini");
                if (File.Exists(iniconfig))
                {
                    readConfig = true;
                }
                else
                {
                    readConfig = OpenViewer.Viewer.CreateDefaultConfig(iniconfig);
                }

                if (readConfig)
                {
                    config.Load(iniconfig);
                }
                else
                {
                    VUtil.LogConsole(this.ToString(), "SetupConfig: ERROR: can't load config file.");
                }
            }
            catch (Exception e)
            {
                VUtil.LogConsole(this.ToString(), "SetupConfig: FETAL:" + e.Message);
            }
        }

        private delegate void ControlAddDelegate(Control control);
        private delegate void ControlShowDelegate();

        public delegate void OnViewerStartupDelegate(bool result);

        public void Load(OnViewerStartupDelegate OnViewerStartup)
        {
            this.Control.Show();
            loadThread = new Thread(new ThreadStart(delegate() { this.DelayedLoad(OnViewerStartup); }));
            loadThread.Start();
        }

        private void DelayedLoad(OnViewerStartupDelegate OnViewerStartup)
        {
            OnViewerStartup(TryDelayedLoad());
        }

        private bool TryDelayedLoad()
        {
            bool isInitSafe = false;

            lock (numberOfInstanceInCurrentClrLock)
            {
                if (0 < numberOfInstanceInCurrentClr)
                {
                    int timeout = 1000;
                    Monitor.Wait(numberOfInstanceInCurrentClrLock, timeout);
                }
                if (numberOfInstanceInCurrentClr == 0)
                {
                    isInitSafe = Util.IsInitSafe();
                    if (isInitSafe)
                    {
                        numberOfInstanceInCurrentClr++;
                        isStarted = true;
                    }
                }
            }
            if (isInitSafe)
            {
                SetupConfig();

                if (CheckDriveSize() == false)
                    return false;

                if (!String.IsNullOrEmpty(RequireVersion) && !IsVersionRequirementSatisfied(RequireVersion))
                {
                    Label warning = new Label();
                    warning.Text = "本サービスをご使用いただくには、3Di OpenViewerのアップデートが必要です。";
                    warning.Location = new Point(10, Height / 2 - 10);
                    warning.Size = new Size(Width - 20, 20);
                    warning.ForeColor = Color.Red;
                    warning.BackColor = Color.White;
                    warning.TextAlign = ContentAlignment.MiddleCenter;
                    this.Control.Invoke(new ControlAddDelegate(this.Control.Controls.Add), warning);
                    LinkLabel link = new LinkLabel();
                    link.Text = "最新の情報はこちらでご覧いただけます。";
                    link.Links.Add(6, 3);
                    link.Location = new Point(10, Height / 2 + 10);
                    link.Size = new Size(Width - 20, 20);
                    link.ForeColor = Color.Red;
                    link.BackColor = Color.White;
                    link.TextAlign = ContentAlignment.MiddleCenter;
                    link.Click += new EventHandler(link_Click);
                    this.Control.Invoke(new ControlAddDelegate(this.Control.Controls.Add), link);
                    PictureBox bg = new PictureBox();
                    Bitmap bitmap = InitBackgroundBitmap;
                    bg.ClientSize = new Size(bitmap.Width, bitmap.Height);
                    bg.Location = new Point((Width - bitmap.Width) / 2, (Height - bitmap.Height) / 2);
                    bg.Image = bitmap;
                    this.Control.Invoke(new ControlAddDelegate(this.Control.Controls.Add), bg);
                    this.Control.Invoke(new ControlShowDelegate(this.Control.Show));
                    return false;
                }
                string versionServer = config.Source.Configs["Startup"].Get("version_server_url", null);
                if (versionServer != null)
                {
                    ShowVersionCheckWindow(versionServer);
                }
                keepAliveTimer = new System.Threading.Timer(new TimerCallback(this.KeepAlive), null, 0, 5000);

                string helpURL = config.Source.Configs["Startup"].Get("help_url", "http://3di-opensim.com/");
                string locale = config.Source.Configs["Startup"].Get("locale", "jp");
                string debugTab = config.Source.Configs["Startup"].Get("debug_tab", "false");
                string cameraReverse = config.Source.Configs["Startup"].Get("reverse_camera_pitch", "false");
                string seaQuality = config.Source.Configs["Shader"].Get("sea_quality", "low");
                string skyQuality = config.Source.Configs["Shader"].Get("sky_quality", "low");
                long teleportTimeout = config.Source.Configs["Startup"].GetLong("teleport_timeout", 20);

                OV.Version = version;
                OV.HelpURL = helpURL;
                OV.Locale = locale;
                OV.IsVisibleDebutTab = (debugTab == "true" ? true : false);
                OV.IsCameraPitchReverse = (cameraReverse == "true" ? true : false);
                OV.SetShaderQuality(OpenViewer.Managers.ShaderManager.ShaderType.Sea, seaQuality);
                OV.SetShaderQuality(OpenViewer.Managers.ShaderManager.ShaderType.AdvancedSea, seaQuality);
                OV.SetShaderQuality(OpenViewer.Managers.ShaderManager.ShaderType.Sky, skyQuality);

                OV.TeleportTimeout = teleportTimeout * 10000000;

                OV.Startup(this.Handle);
                return true;
            }
            else
            {
                Label warning = new Label();
                warning.Text = "複数の3Di OpenViewerを同時に使用することはできません\r\nこちらのページをご覧になる前に、ご使用中の3Di OpenViewerをすべて閉じてください。";
                warning.Location = new Point(10, Height / 2 - 20);
                warning.Size = new Size(Width - 20, 40);
                warning.ForeColor = Color.Red;
                warning.BackColor = Color.White;
                warning.TextAlign = ContentAlignment.MiddleCenter;
                this.Control.Invoke(new ControlAddDelegate(this.Control.Controls.Add), warning);
                PictureBox bg = new PictureBox();
                Bitmap bitmap = InitBackgroundBitmap;
                bg.ClientSize = new Size(bitmap.Width, bitmap.Height);
                bg.Location = new Point((Width - bitmap.Width) / 2, (Height - bitmap.Height) / 2);
                bg.Image = bitmap;
                this.Control.Invoke(new ControlAddDelegate(this.Control.Controls.Add), bg);
                this.Control.Invoke(new ControlShowDelegate(this.Control.Show));
                return false;
            }
        }

        private void KeepAlive(object param)
        {
            //int PID = System.Diagnostics.Process.GetCurrentProcess().Id;
            long ticks = DateTime.Now.Ticks;

            // Format: PID:ticks
            try
            {
                const string keepaliveFile = "keepalive";
                System.IO.StreamWriter sw = new StreamWriter(Util.UserCacheDirectory + @"\" + keepaliveFile, false);
                sw.WriteLine(this.keepaliveUUID.ToString() + ":" + ticks.ToString());
                sw.Close();
            }
            catch
            {
            }
        }

        public static string GetExePath()
        {
            try
            {
                RegistryKey mozilla = Registry.LocalMachine.OpenSubKey("SOFTWARE").OpenSubKey("Mozilla");
                string name = "Mozilla Firefox";

                foreach (string subkey in mozilla.GetSubKeyNames())
                {
                    if (subkey.Length < name.Length)
                        continue;
                    if (subkey.Substring(0, name.Length) != name)
                        continue;
                    try
                    {
                        return (string)mozilla.OpenSubKey(subkey).OpenSubKey("bin").GetValue("PathToExe");
                    }
                    catch
                    {
                    }
                }
            }
            catch
            {
            }
            return null;
        }
        
        public void link_Click(object sender, EventArgs e)
        {
            string path = GetExePath();
            string location = config.Source.Configs["Startup"].Get("help_url", "http://3di-opensim.com/openviewer/");

            if (String.IsNullOrEmpty(path))
                return;

            try
            {
                ProcessStartInfo info = new ProcessStartInfo();
                info.FileName = path;
                info.Arguments = location;
                info.UseShellExecute = true;
                System.Diagnostics.Process.Start(info);
            }
            catch
            {
            }
        }

        public void Shutdown()
        {
            OV.Shutdown();
            if (keepAliveTimer != null)
            {
                keepAliveTimer.Dispose();
                Util.CloseKeepAlive();
            }
            if (loadThread != null)
            {
                loadThread.Join();
            }
            if (isStarted)
            {
                lock (numberOfInstanceInCurrentClrLock)
                {
                    numberOfInstanceInCurrentClr--;
                    Monitor.PulseAll(numberOfInstanceInCurrentClrLock);
                }
            }
        }
    }
}
