<!DOCTYPE html>
<!-- saved from url=(0065)https://www.w3schools.com/html/tryit.asp?filename=tryhtml_default -->
<html lang="en-US">

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title>Tryit Editor v3.5</title>
    <meta name="viewport" content="width=device-width">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="w3.css">
    <link rel="stylesheet" href="style.css">
</head>

<body>
    <script>
        function submit() {
            document.getElementById("codeForm").submit()
        }
    </script>
    <div class="trytopnav">
        <div class="w3-bar w3-light-grey" style="border-top:1px solid #f1f1f1;overflow:auto">
            <button class="w3-button w3-bar-item w3-red w3-hover-white w3-hover-text-red" onclick="submitTryit(1)">Upload »</button>
            <button class="w3-button w3-bar-item w3-green w3-hover-white w3-hover-text-green" onclick="submit()">Run »</button>
            <span class="w3-right w3-hide-medium w3-hide-small" style="padding:8px 8px 8px 8px;display:block"></span>
            <span class="w3-right w3-hide-small" style="padding:8px 0;display:block;float:right;"><span id="framesize">端茶倒水小组<span> C语言解释器v1.01</span></span>
            </span>
        </div>
    </div>
    <div id="shield" style="display: none;"></div>
    <a href="javascript:void(0)" id="" style="width: 5px; top: 138px; left: 715px; height: 633px; cursor: col-resize;"></a>
    <div id="container">
        <div id="textareacontainer">
            <form id="codeForm" action="index.php" method="get" style="height:100%; width:100%">
                <div id="textarea">
                    <div id="textareawrapper">
                        <textarea autocomplete="off" name="codeInput" id="textareaCode" wrap="logical" spellcheck="false" style=""><?php
        $defaultInput = '#include <stdio.h>;

int main() {
    print("hello 端茶倒水组！");
}';

        if(isset($_GET['codeInput'])){
            echo $_GET['codeInput'];
        } else {
            echo $defaultInput;
        }

    ?></textarea>
                    </div>
                </div>
            </form>
        </div>
        <div id="resultcontainer">
            <div id="result">
                <div id="resultwrapper" style="padding: 10px">
                    <?php
                        $okMsg = "<span style='background-color: green; color: white'>解释成功！</span>";
                        $errMsg = "<span style='background-color: red; color: white'>解释失败！</span>";

                        $defaultLog = "hello 端茶倒水组！";

                        if (isset($_GET['codeInput'])) {
                            echo '(等待真实程序模块！)<br/>';
                            $command = './demo';
                            $result = exec($command);
                            $result = str_replace('/n', '<br/>', $result);
                            if($result != ''){
                                echo $okMsg;
                                echo '<br/><br/>';
                                echo $result;
                            } else {
                                echo $errMsg;
                            }
                        } else {
                            echo $okMsg;
                            echo '<br /><br/>';
                            echo $defaultLog;
                        }
                    ?>
                    
                </div>
            </div>
        </div>
    </div>
</body>

</html>