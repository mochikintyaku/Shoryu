namespace ui
{
    partial class MainForm
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
            shogiBoardControl1 = new ShogiBoardControl();
            SuspendLayout();
            // 
            // shogiBoardControl1
            // 
            shogiBoardControl1.Dock = DockStyle.Fill;
            shogiBoardControl1.Location = new Point(191, 32);
            shogiBoardControl1.Name = "shogiBoardControl1";
            shogiBoardControl1.Size = new Size(410, 392);
            shogiBoardControl1.TabIndex = 0;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(shogiBoardControl1);
            Name = "MainForm";
            Text = "Shoryu";
            ResumeLayout(false);
        }

        #endregion

        private ShogiBoardControl shogiBoardControl1;
    }
}
