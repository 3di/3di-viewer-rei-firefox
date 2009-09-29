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
using System.Diagnostics;
using System.IO;
using OpenViewer;
using OpenViewer.bootstrap;

namespace OpenViewerKeepAlive
{
    class OpenViewerKeepAlive
    {
        static void Main(string[] args)
        {
            if (!Util.IsInitSafe())
            {
                Environment.Exit(1);
            }

            string exePath = OpenViewer.bootstrap.Bootstrap.GetExePath();
            if (!String.IsNullOrEmpty(exePath))
            {
                string dllPath = Path.Combine(Path.GetDirectoryName(exePath), "OpenViewer.dll");

                foreach (Process p in Process.GetProcessesByName("firefox"))
                {
                    foreach (ProcessModule mo in p.Modules)
                    {
                        if (String.Compare(dllPath, mo.FileName, true) == 0)
                        {
                            Environment.Exit(3);
                        }
                    }
                }
            }
            Environment.Exit(0);
        }
    }
}
