<h1>КОМАНДНЫЙ ПРОЕКТ для лабораторной работы №12 по дисциплине "Основы программной инженерии"

<h2>СТРУКТУРА ПРОЕКТА</h2>

<h3>Если кратко:</h3>
<p>
В main() есть главное меню, в котором пользователь может выбрать вариант выполнения программы. Для решения своей задачи из лр 12 нужно написать одну функцию типа void (при необходимости она может вызывать подфункции). Эта функция будет вызываться из main(), если пользователь выберет в главном меню соответствующий вариант действия. Каждый член команды создаст один заголовочный файл .h с прототипом(-ами) своей(-их) функции(-й) (прототипы подфункций тоже там) и один файл реализации .cpp с определениями всех своих функций из .h. Эти два файла нужно будет отправить сюда, на удалённый репозиторий (как это сделать? - описано ниже).
</p>

<h3>Проект содержит в себе:</h3>
<ul>
  <li> Файл main.cpp с главным меню программы</li>
  <li> Заголовочный файл (.h) для каждого решения задания из лр 12</li>
  <li> Файл реализации (.cpp) для каждого решения задания из лр 12</li>
</ul>

<h4>main.cpp</h4>
<p>
Главный файл программы. В начале файла прописываются директивы #include для подключения заголовочных файлов. При запуске программы отображается меню с выбором дальнейших действий (каждый вариант выбора - одно из заданий лр 12), также есть вариант завершить выполнение программы.
</p>

<h4>Заголовочные файлы</h4>
<p>
Для каждого задания нужно создать один файл заголовка и один файл реализации. Имя файла заголовка практически совпадает с именем функции для выполнения задания (эта функция вызывается из главного меню в main() ).<br>
<i>Пример:</i> если функция задания имеет имя stringCalculator, то заголовочный файл будет иметь имя string_calculator(.h)<br>
Файл заголовка должен иметь следующую структуру:<br>
    <pre>
    #ifndef ИМЯ_ФАЙЛА_ЗАГОЛОВКА_H
    #define ИМЯ_ФАЙЛА_ЗАГОЛОВКА_H<br>
    // Здесь перечисляются прототипы (объявления) всех функций, используемых в файле реализации (без определений этих функций).<br>
    #endif</pre>
</p>

<h4>Файлы реализации</h4>
<p>
Вместе с заголовочным файлом нужно создать файл реализации, где будут определены функции, описанные в файле заголовка. Имя файла реализации полностью совпадает с именем соответствующего заголовка, за исключением расширения .cpp вместо .h<br>
<i>Пример:</i> если функция задания имеет имя stringCalculator, то файл реализации будет иметь имя string_calculator(.cpp)<br><br>
В зависимости от задания, файл реализации имеет одну из двух следующих структур:<br>
<br>
1) Если задача условно неделима, то сначала выполняется основная функция задачи, затем выводится меню выбора: выполнить задачу ещё раз, выйти в меню или выйти из программы.<br>
<i>Пример: задача - вывод текущего времени.</i><br>
Пользователь в главном меню (в main() ) выбирает вариант "вывести текущее время", main() вызывает функцию void currentTime() (прототип функции в current_time.h, реализация в current_time.cpp), функция сначала выводит текущее время, затем выводит меню выбора: вывести текущее время (т.е. снова), перейти в меню или выйти из программы. <b>Шаблон кода: см. testFunc1.h и testFunc1.cpp</b><br>
<br>
2) Если задача делимая, т.е. если пользователь сразу выбирает, что будет делать программа, то сначала выводится меню выбора: выполнить первую подзадачу, выполнить вторую подзадачу, выйти в меню или выйти из программы - и только потом выполняется подзадача. Обратите внимание: в первом случае сначала хотя бы раз выполняется задача, во втором можно вернуться в меню до выполнения задачи.<br>
<i>Пример: задача - перевод числа из двоичной системы счисления в десятичную и наоборот.</i><br>
Пользователь в главном меню (в main() ) выбирает вариант "перевести число из...", main() вызывает функцию void binDecConverter() (прототип функции в bin_dec_converter.h, реализация в bin_dec_converter.cpp), функция сначала выводит меню выбора: перевести число из 2-й сист. сч. в 10-ую,  перевести число из 10-й сист. сч. в 2-ую, перейти в меню или выйти из программы - и потом, после выбора пользователя, выполняется перевод введённого числа в нужную систему счисления. <b>Шаблон кода: см. testFunc2.h и testFunc2.cpp</b><br>
<br>
<b>Это необязательно</b>, но мне кажется, что реализация циклического выполнения вашей функции с возможностью перейти в меню или выйти из программы удобнее автоматического завершения функции с выходом в меню. Так или иначе, если это не сделаете вы, это сделаю я. Но вы можете сделать мою жизнь чуточку проще.  
</p>

<h2>Начало работы</h2>
<p>Чтобы начать работу над своим заданием, нужно:<br>
  <ol>
    <li>
      <ul><b>Клонировать себе этот репозиторий</b>
        <li>Запустить Visual Studio</li>
        <li>Нажать "Клонирование репозитория"</li>
        <li>Дальше нужно ввести ссылку на этот репозиторий ( https://github.com/Aliaksiej-Ramanchuk/emap ) и указать (создать) пустую папку, куда будет клонирован репозиторий</li>
        <li>Нажать "Клонировать"</li>
      </ul>
    </li>
    <li>
      <ul><b>Найти файлы полученного проекта</b>
        <li>Дважды нажать в обозревателе решений на emap.sln (в папке решения будут все нужные файлы проекта)</li>
      </ul>
    </li>
    <li>
      <ul><b>Выполнить своё задание</b>
        <li>Добавить в проект файл заголовка и файл реализации для функции, выполняющей ваше задание</li>
        <li>Собственно написать свои файлы заголовка (один файл с прототипами всех ваших функций) и реализации (один файл со всеми определениями функций)</li>
        <li>В главном файле main.cpp добавить <code>#include "имя_заголовочного_файла.h"</code></li>
        <li>В функции main() в соответствующем cout'е (где вывод главного меню) написать название своего задания (лучше кратко)</li>
        <li>В функции main(), где идут switch-case'ы, в соответствующем case прописать название своей функции (она будет вызываться из этого главного меню)</li>
        <li>
          <ul>Проверить, что...
            <li>...ничего не падает</li>
            <li>...задача выполнена (хотя бы частично, но доделать потом)</li>
            <li>...есть надёжная защита от некорректного ввода (с std::cin используйте char или std::string, а не int/double и обрабатывайте ввод как текст). Не получается? Оставьте как есть, сам подправлю</li>
            <li>...стиль написания кода такой же, как и в остальном проекте (camelCase для переменных и функций, UPPER_CASE для констант, snake_case для файлов, везде одинаково расставлены пробелы, переносы строк, все переменные (за исключением, может, итераторов) и функции имеют <u>осмысленные</u> имена и т.д. и т.п.).</li>
          </ul>
        </li>
        <li>Есть проблемы? - посмотрите примеры для testFunc1 и testFunc2, посмотрите, как делают другие, или просто спросите "А как..."
        <li><b>Всё равно ничего не понятно? - сделайте хоть что-нибудь хоть как-нибудь, а я подправлю (в крайнем случае напишу с нуля, мне всё-таки отвечать за этот нежизнеспособный проект). Но не затягивайте до последней лабы.</b></li>
      </ul>
    </li>
    <li>
      <ul><b>Сохранить и отправить свои изменения на удалённый репозиторий (сюда)</b>
        <li>В меню Visual Studio найдите и откройте вкладку Git (в сааамом верху, между Вид и Проект)</li>
        <li>В выпадающем меню нажмите "Фиксация или скрытие", чтобы создать локальный коммит</li>
        <li>Справа нужно написать комментарий к коммиту (там где "Введите сообщение <Required>")</li>
        <li>Нажмите "Зафиксировать все"</li>
        <li>Снова откройте вкладку Git, нажмите "Отправить"</li>
        <li>Если всё хорошо, то изменения уже применились в удалённом репозитории. Но может произойти и конфликт слияния: он решается вручную прямо в Visual Studio. Экран разделится на три области (что в удалённом репозитории, что в локальном и область решения конфликта) После решения конфликта нужно будет нажать "Принять слияние", зафиксировать и (кажется) снова отправить</li>
      </ul>
    </li>
  </ol>
</p>

<h2>Прочее, но <b>важное</b></h2>
<p>
Основную (наверное, практически всю) <b>документацию</b> проекта буду вести я. К сожалению, в самом файле лр не сказано, что должна включать в себя документация проекта, поэтому я собираюсь сегодня решить этот вопрос.<br>
<br>
Вообще говоря, сначала нужно создать т.н. <b>бэклог продукта</b>, где будут описываться все требования к нашим функциям (пользовательские истории типа "как пользователь, я хочу использовать программу для чтения текстовых файлов, чтобы не порезать палец о край страницы печатной книги"), и уже <i>на основе пользовательских историй</i> писать программу проекта. Я так понимаю, это должен быть отдельный файл word с табличкой (создам его я), как в файле лр, и этот файл должен быть на удалённом репозитории, и каждый может добавлять туда свои пользовательские истории. Я завтра тоже уточню насчёт этого. Было бы хорошо и просто замечательно, если бы вы сами писали пользовательские истории для своих программ (ещё лучше (т.е. как надо) - заранее, до того, как сели писать программу).<br>
<b>Бэклог спринта</b>. Я так понимаю, это либо ещё один файл word, в котором мы должны писать наши планы на ближайшее будущее в отношении проекта (даём обещания, что сделаем, и реальные сроки, когда мы эти обещания выполним), либо составная часть файла документации. А может, документация и должна быть многофайловой. Кто знает. Писать бэклог спринта мы должны либо совместно, либо только я, но перед этим всё с вами обсудив (я же не знаю ваших ваших планов).<br>
<br>
В файле лр предлагается организовать работу при помощи <b>kanban-доски</b> либо при помощи <b>issues</b> в Github'е. У меня нет идей, как эффективно реализовать kanban-доску, поэтому я бы удовлетворился issues. Создавать их просто, закрывать тоже. По сути та же доска.<br>
<br>
<b>Диаграмма вариантов</b> для каждого модуля программы. Я так понимаю, это значит сделать схему для каждой нашей функции, решающей задачу (у нас они модули). Про эти диаграммы можно почитать тут: https://habr.com/ru/post/566218 , но я лучше уточню, это ли от нас требуют. По сути мы просто разворачиваем меню каждой функции в небольшую схему. Буду весьма признателен, если вы сами сделаете такие схемы для своих функций. Головной модуль (главное меню) возьму я. У кого-то схемы будут из двух эллипсов, у кого-то побольше. Как повезёт. Я не знаю, где именно должны быть эти диаграммы, но я подозреваю, что в главном (единственном?) файле документации.<br>
<br>
<b>Система тестов</b>. Тут нужно будет для каждого действия в программе написать последствия, разбив всё на шаги. Было бы хорошо, если бы вы сами написали небольшие системы тестов для своих программ, а я бы потом их включил в общую систему тестов, которая будет либо в отдельном файле, либо в файле документации, либо в том же файле, что и диаграммы вариантов (всё-таки они тесно связаны). Нужно будет уточнить и этот вопрос.<br>
<br>
Неясностей хватает, но в общем не так уж и сложно.
</p>

<h3>Узаемадапамога</h3>
<p>
Бачыце, што нехта ўвогуле не разумее, што рабіць? Што ў кагосьці штосьці не атрымліваецца? Што тут лепш зрабіць так, а там увогуле лагічная памылка? - растлумачце, парайце, выпраўце! Не заставайцеся ўбаку! Дапамагайма адно аднаму.
</p>

<p> - Раманчук Аляксей</p>
