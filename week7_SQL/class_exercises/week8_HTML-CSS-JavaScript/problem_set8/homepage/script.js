function sendMessage()
{
    let name = document.querySelector('#name').value;
    let email = document.querySelector('#email').value;
    let message = document.querySelector('#message').value;

    if (name === '' || email === '' || message === '')
    {
        document.querySelector('.alert').style.display = 'block';
    }
    else
    {
        alert("There is no Backend")
    }
}

function hidde(){
    document.querySelector('.alert').style.display = 'none';
}
