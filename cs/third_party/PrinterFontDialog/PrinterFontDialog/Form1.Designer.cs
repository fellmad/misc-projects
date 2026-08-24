namespace PrinterFontDialog
{
    partial class Form1
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lblExample = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtPrinterName = new System.Windows.Forms.TextBox();
            this.btnNetFont = new ToolboxDll.CustomButton();
            this.btnComFont = new ToolboxDll.CustomButton();
            this.SuspendLayout();
            // 
            // lblExample
            // 
            this.lblExample.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.lblExample.Location = new System.Drawing.Point(9, 123);
            this.lblExample.Name = "lblExample";
            this.lblExample.Size = new System.Drawing.Size(271, 58);
            this.lblExample.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(7, 106);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Preview :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Printer Name :";
            // 
            // txtPrinterName
            // 
            this.txtPrinterName.Location = new System.Drawing.Point(93, 10);
            this.txtPrinterName.Name = "txtPrinterName";
            this.txtPrinterName.Size = new System.Drawing.Size(187, 20);
            this.txtPrinterName.TabIndex = 5;
            // 
            // btnNetFont
            // 
            this.btnNetFont.Location = new System.Drawing.Point(10, 50);
            this.btnNetFont.Name = "btnNetFont";
            this.btnNetFont.Size = new System.Drawing.Size(96, 42);
            this.btnNetFont.TabIndex = 6;
            this.btnNetFont.Text = ".NET Font Dialog";
            this.btnNetFont.TextMode = ToolboxDll.TextMode.None;
            this.btnNetFont.UseVisualStyleBackColor = true;
            this.btnNetFont.Click += new System.EventHandler(this.ButtonClickHandler);
            // 
            // btnComFont
            // 
            this.btnComFont.Location = new System.Drawing.Point(112, 50);
            this.btnComFont.Name = "btnComFont";
            this.btnComFont.Size = new System.Drawing.Size(103, 42);
            this.btnComFont.TabIndex = 7;
            this.btnComFont.Text = "COM Font Dialog";
            this.btnComFont.TextMode = ToolboxDll.TextMode.None;
            this.btnComFont.UseVisualStyleBackColor = true;
            this.btnComFont.Click += new System.EventHandler(this.ButtonClickHandler);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(290, 196);
            this.Controls.Add(this.btnComFont);
            this.Controls.Add(this.btnNetFont);
            this.Controls.Add(this.txtPrinterName);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lblExample);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Test Printer Fonts Dialog";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblExample;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtPrinterName;
        private ToolboxDll.CustomButton btnNetFont;
        private ToolboxDll.CustomButton btnComFont;
    }
}

