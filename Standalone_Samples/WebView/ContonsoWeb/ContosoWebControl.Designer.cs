using System.Windows.Forms;

namespace ContosoApp
{
    partial class ContosoWebControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
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
            this.webView = new Microsoft.Toolkit.Forms.UI.Controls.WebView();
            this.goBackButton = new Button();

            ((System.ComponentModel.ISupportInitialize)(this.webView)).BeginInit();
            this.SuspendLayout();
            // 
            // webView
            // 
            this.webView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.webView.Location = new System.Drawing.Point(0, 00);
            this.webView.Name = "webView";
            this.webView.Size = new System.Drawing.Size(1194, 474);
            this.webView.TabIndex = 0;
            this.webView.TabStop = false;

            // 
            // goBackButton
            // 
            this.goBackButton.Location = new System.Drawing.Point(0, 0);
            this.goBackButton.Name = "goBackButton";
            this.goBackButton.Text = "Go Back";
            this.goBackButton.Size = new System.Drawing.Size(200, 50);
            this.goBackButton.TabIndex = 0;
            this.goBackButton.TabStop = false;
            this.goBackButton.Click += OnGoBackButtonClick;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 30F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1194, 474);
            this.Controls.Add(this.goBackButton);
            this.Controls.Add(this.webView);
            this.Name = "ContosoWebControl";
            this.Text = "Contoso Web Control";
            ((System.ComponentModel.ISupportInitialize)(this.webView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private Microsoft.Toolkit.Forms.UI.Controls.WebView webView;
        private Button goBackButton;
    }
}
