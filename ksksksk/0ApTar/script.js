document.addEventListener('DOMContentLoaded', () => {
    // Referências aos elementos HTML
    const inputNovaTarefa = document.getElementById('nova-tarefa');
    const btnAdicionarTarefa = document.getElementById('btn-adicionar');
    const listaTarefas = document.getElementById('tarefas');
    const divErro = document.getElementById('erro-input');

    // Adiciona tarefa ao clicar no botão
    btnAdicionarTarefa.addEventListener('click', adicionarTarefa);

    // Adiciona tarefa ao pressionar Enter no campo de entrada
    inputNovaTarefa.addEventListener('keypress', (event) => {
        if (event.key === 'Enter') {
            adicionarTarefa();
        }
    });

    // Função para adicionar uma nova tarefa
    function adicionarTarefa() {
        const textoTarefa = inputNovaTarefa.value.trim();

        // Validação: campo vazio
        if (textoTarefa === '') {
            divErro.textContent = 'Por favor, digite uma tarefa.';
            return;
        }

        // Limpa mensagem de erro se houver
        divErro.textContent = '';

        // Criação do elemento <li>
        const li = document.createElement('li');

        // Criação do <span> com texto da tarefa
        const tarefaTextoSpan = document.createElement('span');
        tarefaTextoSpan.classList.add('tarefa-texto');
        tarefaTextoSpan.textContent = textoTarefa;

        // Criação da <div> de ações
        const divAcoes = document.createElement('div');
        divAcoes.classList.add('acoes');

        // Botão "Concluir"
        const btnConcluir = document.createElement('button');
        btnConcluir.textContent = 'Concluir';
        btnConcluir.classList.add('btn-concluir');

        // Evento para marcar/desmarcar como concluída
        btnConcluir.addEventListener('click', () => {
            tarefaTextoSpan.classList.toggle('concluida');
        });

        // Botão "Remover"
        const btnRemover = document.createElement('button');
        btnRemover.textContent = 'Remover';
        btnRemover.classList.add('btn-remover');

        // Evento para remover a tarefa da lista
        btnRemover.addEventListener('click', () => {
            listaTarefas.removeChild(li);
        });

        // Monta a estrutura
        divAcoes.appendChild(btnConcluir);
        divAcoes.appendChild(btnRemover);
        li.appendChild(tarefaTextoSpan);
        li.appendChild(divAcoes);
        listaTarefas.appendChild(li);

        // Limpa o campo de entrada
        inputNovaTarefa.value = '';
    }
});
