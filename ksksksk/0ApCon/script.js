document.addEventListener('DOMContentLoaded', () => {
    // Referências aos elementos do DOM
    const valorContadorElement = document.getElementById('valor-contador');
    const incrementarBtn = document.getElementById('incrementar-btn'); // Corrigido
    const decrementarBtn = document.getElementById('decrementar-btn'); // Corrigido
    const resetarBtn = document.getElementById('resetar-btn');         // Corrigido
    const erro = document.getElementById('erro-mensagem');

    // Inicialização do contador
    let contador = 0;

    // Atualiza o valor exibido na tela e limpa erro
    function atualizarContador() {
        valorContadorElement.textContent = contador;
        erro.style.display = 'none'; // Oculta qualquer mensagem de erro ao atualizar
    }

    // Incrementar
    incrementarBtn.addEventListener('click', () => {
        contador++;
        atualizarContador();
    });

    // Decrementar
    decrementarBtn.addEventListener('click', () => {
        if (contador > 0) {
            contador--;
            atualizarContador();
        } else {
            erro.textContent = "O valor não pode ser negativo.";
            erro.style.display = 'block';
        }
    });

    // Resetar
    resetarBtn.addEventListener('click', () => {
        contador = 0;
        atualizarContador();
    });

    // Exibir valor inicial
    atualizarContador();
});
