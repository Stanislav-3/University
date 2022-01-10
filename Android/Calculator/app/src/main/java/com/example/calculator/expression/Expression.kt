package com.example.calculator.expression

import android.util.Log
import com.example.calculator.R
import com.example.calculator.expression_part.ComplexOperation
import com.example.calculator.expression_part.ExpressionPart
import com.example.calculator.expression_part.NumberPart
import com.example.calculator.expression_part.OperationSign
import com.example.calculator.extentions.toBeautyString
import org.mariuszgromada.math.mxparser.Function
import java.util.*
import java.util.stream.Collector
import org.mariuszgromada.math.mxparser.Expression as ParserExpression

class Expression {
    private var lg: Function = Function("lg(x) = ln(x) / ln(10)")

    public var content: MutableList<ExpressionPart> = mutableListOf()

    private var isHardSolved: Boolean = false

    private val max_len = 6

    fun getBeautyExpression(): String {
        var expression = ""

        for (expressionPart in content){
            expression += expressionPart.getBeautyContent()
        }

        return expression
    }

    fun countDigits(newExpressionPart: ExpressionPart=NumberPart("0")): Int {
        var len = 0
        if (newExpressionPart is NumberPart || newExpressionPart.getInternalString() == ".") {
            var pointCount = 0
            var i = content.size - 1
            while (i >= 0 && pointCount < 1) {
                if (content[i].getInternalString() == "."){
                    pointCount++
                }
                else if (content[i] is NumberPart){
                    len++
                } else return len
                i--
            }
        }
        return len
    }

    fun append(newExpressionPart: ExpressionPart, full: Boolean = false){
        if (newExpressionPart is OperationSign && content.lastOrNull() is OperationSign){
            val expr = newExpressionPart.getInternalString()
            if (content.last().getInternalString() == "-"
                && (content.size == 1 || content[content.size - 2] !is NumberPart)) {
                return
            }
            content[content.size - 1] = newExpressionPart
            return
        }

        if (content.lastOrNull() == null) {
            val expr = newExpressionPart.getInternalString()
            if (expr == "." || expr == ")" || expr == "^" || expr == "^(-1)" || expr == "^2"
                || expr == "^3" || expr == "!" || expr == "*" || expr == "/" || expr == "+") {
                return
            }
        }

        if (newExpressionPart.getInternalString() == ".") {
            var i = content.size - 1
            while (i >= 0 && content[i] is NumberPart){
                if (content[i].getInternalString() == "."){
                    return
                }
                i--
            }
        }

        if (newExpressionPart is NumberPart && newExpressionPart.getInternalString() != "."
            && content.lastOrNull() is NumberPart && content.last().getInternalString() == "0"
            && (content.size == 1 || content[content.size - 2] !is NumberPart)) content.removeLast()

        if (!full && countDigits(newExpressionPart) >= max_len) return

        content.add(newExpressionPart)
    }

    fun clear(){
        content.clear()
    }

    fun backspace(){
        content.removeLastOrNull()
    }

    fun percent() {
        val newContent = content.toMutableList()
        var lastNumber = ""
        while (newContent.lastOrNull() is NumberPart){
            lastNumber = newContent.last().getInternalString() + lastNumber
            newContent.removeLast()
        }
        if (lastNumber == ""){
            return
        }
        val expressionResult = getResult(newContent)
        val newLastNumber: String

        val expressionPercentage = newContent.size > 1 && (newContent.last().getInternalString() in "-+")

        newLastNumber = if (expressionPercentage && expressionResult.isValid && expressionResult.value.isFinite()){
            (expressionResult.value * lastNumber.toDouble() / 100).toBeautyString()
        } else{
            (lastNumber.toDouble() / 100).toBeautyString()
        }
        for (numberCharacter in newLastNumber){
            when (numberCharacter){
                '-' -> {
                    if (newContent.size == 0 || newContent.last().getInternalString() !in "-+"){
                        throw UnsupportedOperationException()
                    }
                    when (newContent.last().getInternalString()){
                        "-" -> newContent[newContent.size - 1] = OperationSign("+")
                        "+" -> newContent[newContent.size - 1] = OperationSign("-")
                    }
                }
                '.' -> newContent.add(NumberPart(",", "."))
                else -> newContent.add(NumberPart(numberCharacter.toString()))
            }
        }
        content = newContent
    }

    fun getResult(hard: Boolean = false): ExpressionResult {
        isHardSolved = hard
        return getResult(content)
    }

    private fun getResult(expression: MutableList<ExpressionPart>): ExpressionResult{
        var expressionString = ""
        for (expressionPartIndex in expression.indices) {
            val expressionPart = expression[expressionPartIndex]
            if (!(expressionPart == expression.last() && expressionPart is OperationSign)) {
                expressionString += expressionPart.getInternalString()
            }
            if (expressionPartIndex != expression.size - 1 && needMultiplication(expressionPart,
                    expression[expressionPartIndex + 1])){
                expressionString += "*"
            }
        }
        if (expressionString.isEmpty()) {
            return ExpressionResult(0.0, true)
        }
        var depth = 0
        expressionString.forEach { character ->
            when (character){
                '(' -> depth++
                ')' -> depth--
            }
        }
        if (depth > 0)
            expressionString += ")".repeat(depth)
        val parserExpression = ParserExpression(expressionString, lg)
        val result = parserExpression.calculate()
        val isValid = parserExpression.checkLexSyntax()

        return ExpressionResult(result, isValid)
    }

    private fun needMultiplication(first: ExpressionPart, second: ExpressionPart): Boolean{
        return first.isRightMultiplicationRequired() && second.isLeftMultiplicationRequired() &&
                !(first is NumberPart && second is NumberPart)
    }

    fun isHardSolved() = isHardSolved

    fun resultToExpression(): String{
        val result = getResult().value.toBeautyString()
        clear()
        val pointInd = result.indexOf('.')
        val strLen = result.length

        var resultStr = ""
        if (strLen <= max_len) {
            for (numberCharacter in result){
                when (numberCharacter){
                    '-' -> { append(OperationSign("-")); resultStr += "-"}
                    '.' -> { append(NumberPart(",", ".")); resultStr += ","}
                    else -> { append(NumberPart(numberCharacter.toString()));
                        resultStr += numberCharacter.toString()}
                }
            }
        } else if (strLen > max_len && (pointInd < 0 || pointInd > max_len)) {
            var i = 0
            for (numberCharacter in result) {
                when (numberCharacter){
                    '-' -> { append(OperationSign("-")); resultStr += "-"}
                    else -> { append(NumberPart(numberCharacter.toString()));
                        resultStr += numberCharacter.toString()}
                }
                i++
                if (i >= max_len) break
            }
            append(OperationSign("×","*"))
            append(OperationSign("×","*"))
            append(NumberPart("1"))
            append(NumberPart("0"))
            append(NumberPart("^(" + (strLen - max_len) + ")"))
            resultStr += "×10^(" + (strLen - max_len) + ")"
        } else if (strLen > max_len && pointInd < max_len) {
            var i = 0
            for (numberCharacter in result) {
                when (numberCharacter){
                    '.' -> continue
                    '-' -> { append(OperationSign("-")); resultStr += "-"}
                    else -> { append(NumberPart(numberCharacter.toString()));
                        resultStr += numberCharacter.toString()}
                }
                i++
                if (i >= max_len) break
            }
            append(OperationSign("×","*"))
            append(OperationSign("×","*"))
            append(NumberPart("1"))
            append(NumberPart("0"))
            append(NumberPart("^(" + (pointInd - max_len) + ")"))
            resultStr += "×10^(" + (pointInd - max_len) + ")"
        }
        return resultStr
    }
}