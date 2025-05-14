document.addEventListener('DOMContentLoaded', () => {
    // Referências aos elementos HTML
    const converterBtn = document.getElementById('converter-btn');
    const inputValor = document.getElementById('valor');
    const moedaOrigem = document.getElementById('moeda-origem');
    const moedaDestino = document.getElementById('moeda-destino');
    const divResultado = document.getElementById('resultado');
    const divErro = document.getElementById('erro-mensagem');

    // Taxas de câmbio fixas (para fins didáticos)
    const taxasDeCambio = {
        'BRL-USD': 0.19,
        'BRL-EUR': 0.18,
        'USD-BRL': 5.26,
        'USD-EUR': 0.92,
        'EUR-BRL': 5.74,
        'EUR-USD': 1.09
    };

    // Adiciona evento ao botão "Converter"
    converterBtn.addEventListener('click', () => {
        // Limpa mensagens anteriores
        divResultado.textContent = '';
        divErro.textContent = '';

        // Lê e converte o valor digitado
        const valor = parseFloat(inputValor.value);
        const origem = moedaOrigem.value;
        const destino = moedaDestino.value;

        // Validação: valor deve ser um número válido
        if (isNaN(valor) || valor <= 0) {
            divErro.textContent = 'Por favor, insira um valor válido maior que zero.';
            return;
        }

        // Validação: moedas não podem ser iguais
        if (origem === destino) {
            divErro.textContent = 'Por favor, selecione moedas diferentes para conversão.';
            return;
        }

        // Chave de busca na tabela de conversão
        const chaveConversao = `${origem}-${destino}`;
        const taxa = taxasDeCambio[chaveConversao];

        // Verifica se há taxa definida para a conversão
        if (taxa) {
            const convertido = (valor * taxa).toFixed(2);
            divResultado.textContent = `${valor} ${origem} equivalem a ${convertido} ${destino}.`;
        } else {
            divErro.textContent = 'Conversão não disponível para as moedas selecionadas.';
        }
    });
});