using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Input;
using System.Windows.Interop;

namespace CustomButton
{
    public partial class MainWindow : Window
    {
        private const int GWL_EXSTYLE = -20;
        private const int WS_EX_NOACTIVATE = 0x08000000;

        [DllImport("user32.dll")]
        private static extern int GetWindowLong(IntPtr hWnd, int nIndex);

        [DllImport("user32.dll")]
        private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        // 1. Declaramos los dos comandos que pusiste en el XAML
        public ICommand Mayor { get; set; }
        public ICommand Menor { get; set; }

        public MainWindow()
        {
            InitializeComponent();

            // 2. Inicializamos los comandos vinculándolos a las acciones de escribir
            Mayor = new RelayCommand(() => EnviarTexto("<"));
            Menor = new RelayCommand(() => EnviarTexto(">"));

            this.DataContext = this;
        }

        // 3. Método mágico que escribe el carácter en la aplicación de fondo
        private void EnviarTexto(string texto)
        {
            try
            {
                // SendWait envía de forma segura las pulsaciones a la ventana activa
                System.Windows.Forms.SendKeys.SendWait(texto);
            }
            catch (Exception ex)
            {
                // En caso de que falle de forma interna (raras ocasiones)
                System.Diagnostics.Debug.WriteLine("Error al escribir: " + ex.Message);
            }
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);
            var helper = new WindowInteropHelper(this);
            IntPtr hwnd = helper.Handle;
            int exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
            SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_NOACTIVATE);
        }
    }

    // 4. Clase auxiliar para hacer funcionar los comandos en el Code-Behind (sin frameworks)
    public class RelayCommand : ICommand
    {
        private readonly Action _execute;
        public RelayCommand(Action execute) => _execute = execute;
        public bool CanExecute(object parameter) => true;
        public void Execute(object parameter) => _execute?.Invoke();
        public event EventHandler CanExecuteChanged;
    }
}
