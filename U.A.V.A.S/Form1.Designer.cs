namespace U.A.V.A.S_
{
    partial class UAVASForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.anomalyBox = new System.Windows.Forms.GroupBox();
            this.videoBox = new System.Windows.Forms.GroupBox();
            this.metaBox = new System.Windows.Forms.GroupBox();
            this.analyzeButton = new System.Windows.Forms.Button();
            this.stopButton = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.settingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // anomalyBox
            // 
            this.anomalyBox.Location = new System.Drawing.Point(18, 27);
            this.anomalyBox.Name = "anomalyBox";
            this.anomalyBox.Size = new System.Drawing.Size(266, 416);
            this.anomalyBox.TabIndex = 0;
            this.anomalyBox.TabStop = false;
            this.anomalyBox.Text = "Anomalies";
            // 
            // videoBox
            // 
            this.videoBox.Location = new System.Drawing.Point(351, 27);
            this.videoBox.Name = "videoBox";
            this.videoBox.Size = new System.Drawing.Size(425, 141);
            this.videoBox.TabIndex = 1;
            this.videoBox.TabStop = false;
            this.videoBox.Text = "Video";
            // 
            // metaBox
            // 
            this.metaBox.Location = new System.Drawing.Point(351, 174);
            this.metaBox.Name = "metaBox";
            this.metaBox.Size = new System.Drawing.Size(425, 154);
            this.metaBox.TabIndex = 2;
            this.metaBox.TabStop = false;
            this.metaBox.Text = "Video Info";
            // 
            // analyzeButton
            // 
            this.analyzeButton.Location = new System.Drawing.Point(351, 335);
            this.analyzeButton.Name = "analyzeButton";
            this.analyzeButton.Size = new System.Drawing.Size(71, 33);
            this.analyzeButton.TabIndex = 3;
            this.analyzeButton.Text = "Analyze";
            this.analyzeButton.UseVisualStyleBackColor = true;
            this.analyzeButton.Click += new System.EventHandler(this.analyzeButton_Click);
            // 
            // stopButton
            // 
            this.stopButton.Location = new System.Drawing.Point(447, 334);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(63, 34);
            this.stopButton.TabIndex = 4;
            this.stopButton.Text = "Stop";
            this.stopButton.UseVisualStyleBackColor = true;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.settingsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 5;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // settingsToolStripMenuItem
            // 
            this.settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.settingsToolStripMenuItem.Text = "Settings";
            // 
            // UAVASForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.stopButton);
            this.Controls.Add(this.analyzeButton);
            this.Controls.Add(this.metaBox);
            this.Controls.Add(this.videoBox);
            this.Controls.Add(this.anomalyBox);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "UAVASForm";
            this.Text = "UAVAS";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private GroupBox anomalyBox;
        private GroupBox videoBox;
        private GroupBox metaBox;
        private Button analyzeButton;
        private Button stopButton;
        private MenuStrip menuStrip1;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem settingsToolStripMenuItem;
    }
}