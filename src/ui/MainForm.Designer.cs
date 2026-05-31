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
            handControl_Gote = new UI.HandControl();
            boardControl = new UI.BoardControl();
            handControl_Sente = new UI.HandControl();
            listView1 = new ListView();
            panel1 = new Panel();
            label2 = new Label();
            label1 = new Label();
            panel2 = new Panel();
            label3 = new Label();
            label4 = new Label();
            panel1.SuspendLayout();
            panel2.SuspendLayout();
            SuspendLayout();
            // 
            // handControl_Gote
            // 
            handControl_Gote.AutoSize = true;
            handControl_Gote.Location = new Point(20, 10);
            handControl_Gote.Name = "handControl_Gote";
            handControl_Gote.Size = new Size(230, 260);
            handControl_Gote.TabIndex = 1;
            // 
            // boardControl
            // 
            boardControl.BackColor = Color.FromArgb(239, 179, 97);
            boardControl.Location = new Point(270, 10);
            boardControl.Name = "boardControl";
            boardControl.Size = new Size(550, 580);
            boardControl.TabIndex = 2;
            // 
            // handControl_Sente
            // 
            handControl_Sente.Location = new Point(840, 330);
            handControl_Sente.Name = "handControl_Sente";
            handControl_Sente.Size = new Size(230, 260);
            handControl_Sente.TabIndex = 3;
            // 
            // listView1
            // 
            listView1.Location = new Point(840, 10);
            listView1.Name = "listView1";
            listView1.Size = new Size(230, 210);
            listView1.TabIndex = 4;
            listView1.UseCompatibleStateImageBehavior = false;
            // 
            // panel1
            // 
            panel1.Controls.Add(label2);
            panel1.Controls.Add(label1);
            panel1.Location = new Point(840, 270);
            panel1.Name = "panel1";
            panel1.Size = new Size(230, 50);
            panel1.TabIndex = 5;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(171, 28);
            label2.Name = "label2";
            label2.Size = new Size(38, 15);
            label2.TabIndex = 1;
            label2.Text = "label2";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(30, 28);
            label1.Name = "label1";
            label1.Size = new Size(38, 15);
            label1.TabIndex = 0;
            label1.Text = "label1";
            // 
            // panel2
            // 
            panel2.Controls.Add(label3);
            panel2.Controls.Add(label4);
            panel2.Location = new Point(20, 280);
            panel2.Name = "panel2";
            panel2.Size = new Size(230, 50);
            panel2.TabIndex = 6;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(171, 28);
            label3.Name = "label3";
            label3.Size = new Size(38, 15);
            label3.TabIndex = 1;
            label3.Text = "label3";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(30, 28);
            label4.Name = "label4";
            label4.Size = new Size(38, 15);
            label4.TabIndex = 0;
            label4.Text = "label4";
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1089, 601);
            Controls.Add(panel2);
            Controls.Add(panel1);
            Controls.Add(listView1);
            Controls.Add(handControl_Sente);
            Controls.Add(boardControl);
            Controls.Add(handControl_Gote);
            Name = "MainForm";
            Text = "Shoryu";
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            panel2.ResumeLayout(false);
            panel2.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private UI.BoardControl boardControl;
        private UI.HandControl handControl_Gote;
        private UI.HandControl handControl_Sente;
        private ListView listView1;
        private Panel panel1;
        private Label label1;
        private Label label2;
        private Panel panel2;
        private Label label3;
        private Label label4;
    }
}
