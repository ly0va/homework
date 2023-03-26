#!/usr/bin/python3

import os
import json
from google.cloud import translate_v2 as translate
from telegram.ext import filters, MessageHandler, ApplicationBuilder, CommandHandler

os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = '/home/redboot/docs/homework/KNU/parallel/translator-bot/creds.json'
languages = json.load(open('languages.json'))
client = translate.Client()

async def start(update, context):
    await context.bot.send_message(
        chat_id=update.effective_chat.id, 
        text="Привіт! Я бот-українчик, буду перекладати твої повідомлення українською мовою. Приємного спілкування!"
    )

# define a function to handle incoming messages
async def handle_message(update, context):
    message = update.message.text
    chat_id = update.effective_chat.id
    
    result = client.translate(message, target_language='uk')
    translation = result['translatedText']
    detected_lang = result['detectedSourceLanguage']
    detected_lang = languages.get(detected_lang, detected_lang)
    response = f'{translation}\n\n(Перекладено з: {detected_lang})'
    
    # send the translated message back to the user
    await context.bot.send_message(chat_id=chat_id, text=response)


if __name__ == '__main__':
    application = ApplicationBuilder().token(BOT_TOKEN).build()
    
    start_handler = CommandHandler('start', start)
    echo_handler = MessageHandler(filters.TEXT & (~filters.COMMAND), handle_message)
    
    application.add_handler(start_handler)
    application.add_handler(echo_handler)

    application.run_polling()
