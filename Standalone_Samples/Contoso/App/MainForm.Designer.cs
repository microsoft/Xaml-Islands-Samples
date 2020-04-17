namespace ContosoApp
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
            this.mainUserControl = new MainUserControl(this);
            //((System.ComponentModel.ISupportInitialize)(this.mainUserControl)).BeginInit();
            this.SuspendLayout();
            // 
            // mainUserControl
            // 
            this.mainUserControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainUserControl.Location = new System.Drawing.Point(0, 0);
            this.mainUserControl.Name = "mainUserControl";
            this.mainUserControl.Size = new System.Drawing.Size(1194, 474);
            this.mainUserControl.TabIndex = 0;
            this.mainUserControl.TabStop = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 30F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1194, 474);
            this.Controls.Add(this.mainUserControl);
            this.Name = "MainForm";
            this.Text = "Main Form";
            //((System.ComponentModel.ISupportInitialize)(this.mainUserControl)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Control mainUserControl;
    }
}

